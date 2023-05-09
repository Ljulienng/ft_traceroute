#include "ft_traceroute.h"
#include "libft.h"

struct addrinfo *global_dest_info = NULL;

int main(int argc, char **argv)
{
	char *destination;
	signal(SIGINT, sigint_handler);

	if (process_arguments(argc, argv, &destination) == -1)
	{
		return EXIT_FAILURE;
	}

	struct addrinfo *dest_info = resolve_destination(destination);
	if (!dest_info)
	{
		return EXIT_FAILURE;
	}
	global_dest_info = dest_info;

	printf("traceroute to %s (%s), %d hops max\n",
		   destination,
		   inet_ntoa(((struct sockaddr_in *)dest_info->ai_addr)->sin_addr),
		   MAX_HOPS);
	perform_traceroute(dest_info);

	clean_up();

	return EXIT_SUCCESS;
}

struct addrinfo *resolve_destination(char *destination)
{
	struct addrinfo hints, *res;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;

	int err = getaddrinfo(destination, NULL, &hints, &res);
	if (err != 0)
	{
		// fprintf(stderr, "Error resolving destination: %s\n", gai_strerror(err));
		ft_putstr_fd("traceroute: unknown host\n", 2);
		return NULL;
	}

	return res;
}

void perform_traceroute(struct addrinfo *dest_info)
{
	int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sockfd < 0)
	{
		ft_putstr_fd("Error creating socket\n", 2);
		// perror("Error creating socket");
		return;
	}

	struct sockaddr_in *dest_addr = (struct sockaddr_in *)dest_info->ai_addr;

	for (int ttl = 1; ttl <= MAX_HOPS; ttl++)
	{
		if (setsockopt(sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) < 0)
		{
			ft_putstr_fd("Error setting TTL\n", 2);
			// perror("Error setting TTL");
			break;
		}

		struct timeval round_trip[ROUND_TRIP_COUNT];
		t_info info = {sockfd, sizeof(struct sockaddr_in), dest_addr, {0}, {0}};

		info.sender_addr.sin_addr.s_addr = request_loop(info, ttl, round_trip);
		if (info.sender_addr.sin_addr.s_addr != 0)
		{
			print_result(round_trip, &info.sender_addr, ttl);
		}
		if (info.sender_addr.sin_addr.s_addr == info.dest_addr->sin_addr.s_addr)
		{
			printf("Destination reached!\n");
			break;
		}
	}

	close(sockfd);
}

ssize_t request_loop(t_info info, int ttl, struct timeval round_trip[ROUND_TRIP_COUNT])
{
	struct timeval start, end;
	int icmp_sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (icmp_sockfd < 0)
	{
		ft_putstr_fd("Error creating ICMP socket\n", 2);
		// perror("Error creating ICMP socket");
		return -1;
	}

	for (int i = 0; i < 3; i++)
	{
		int dest_port = 33434 + ttl; // Incrementing port number for each TTL
		info.dest_addr->sin_port = htons(dest_port);

		gettimeofday(&start, NULL);
		if (sendto(info.sockfd, NULL, 0, 0, (struct sockaddr *)info.dest_addr, sizeof(*info.dest_addr)) < 0)
		{
			ft_putstr_fd("Error sending packet\n", 2);
			// perror("Error sending packet");
			break;
		}

		fd_set read_fds;
		FD_ZERO(&read_fds);
		FD_SET(icmp_sockfd, &read_fds);

		struct timeval timeout;
		timeout.tv_sec = 3;
		timeout.tv_usec = 0;

		int ready = select(icmp_sockfd + 1, &read_fds, NULL, NULL, &timeout);
		if (ready < 0)
		{
			ft_putstr_fd("Error with select\n", 2);
			// perror("Error with select");
			break;
		}
		else if (ready == 0)
		{
			if (i == 0)
			{
				ft_putnbr_fd(ttl, 1);
				ft_putstr_fd("   *  ", 1);
			}
			else if (i != 2)
			{
				ft_putstr_fd("*  ", 1);
			}
			else
			{
				ft_putstr_fd("*\n", 1);
			}
			continue;
		}

		char recv_buf[sizeof(struct iphdr) + sizeof(struct icmphdr)];
		ssize_t recv_len = recvfrom(icmp_sockfd, recv_buf, sizeof(recv_buf), 0, (struct sockaddr *)&info.sender_addr, &info.addr_len);
		if (recv_len < 0)
		{
			ft_putstr_fd("Error receiving packet\n", 2);
			// ("Error receiving packet");
			break;
		}
		gettimeofday(&end, NULL);
		// timersub(&end, &start, &round_trip[i]);
		my_timersub(&end, &start, &round_trip[i]);

		struct icmphdr *recv_icmp = (struct icmphdr *)(recv_buf + sizeof(struct iphdr));
		if (recv_icmp->type == ICMP_TIME_EXCEEDED || recv_icmp->type == ICMP_DEST_UNREACH)
		{
			continue;
		}
	}

	close(icmp_sockfd);
	return info.sender_addr.sin_addr.s_addr;
}
