#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <netinet/ip_icmp.h>

#define MAX_HOPS 30

typedef struct s_hop
{
	char *ip;
	double rtt;
} t_hop;

// Function declarations
void print_help();
int process_arguments(int argc, char **argv, char **destination);
struct addrinfo *resolve_destination(char *destination);
void perform_traceroute(struct addrinfo *dest_info);
void print_result(struct timeval *start, struct timeval *end, struct sockaddr_in *sender_addr);
void clean_up(struct addrinfo *dest_info);

int main(int argc, char **argv)
{
	char *destination;

	if (process_arguments(argc, argv, &destination) == -1)
	{
		return EXIT_FAILURE;
	}

	struct addrinfo *dest_info = resolve_destination(destination);
	if (!dest_info)
	{
		return EXIT_FAILURE;
	}

	perform_traceroute(dest_info);

	clean_up(dest_info);

	return EXIT_SUCCESS;
}

void print_help()
{
	printf("Usage: ft_traceroute [destination]\n");
	printf("Destination: IPv4 address or hostname\n");
	printf("Options:\n");
	printf("  --help  Display this help message\n");
}

int process_arguments(int argc, char **argv, char **destination)
{
	if (argc != 2)
	{
		print_help();
		return -1;
	}

	if (strcmp(argv[1], "--help") == 0)
	{
		print_help();
		return -1;
	}

	*destination = argv[1];
	return 0;
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
		fprintf(stderr, "Error resolving destination: %s\n", gai_strerror(err));
		return NULL;
	}

	return res;
}

uint16_t icmp_checksum(const void *data, size_t len)
{
	const uint16_t *words = data;
	unsigned sum = 0;
	for (size_t i = 0; i < len / 2; i++)
	{
		sum += words[i];
	}
	if (len % 2)
	{
		sum += *((uint8_t *)data + len - 1);
	}
	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	return ~sum;
}

void perform_traceroute(struct addrinfo *dest_info)
{
	int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sockfd < 0)
	{
		perror("Error creating socket");
		return;
	}

	struct sockaddr_in *dest_addr = (struct sockaddr_in *)dest_info->ai_addr;

	// Set the ID for ICMP header
	int icmp_request_id = getpid() & 0xFFFF;

	for (int ttl = 1; ttl <= MAX_HOPS; ttl++)
	{
		if (setsockopt(sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) < 0)
		{
			perror("Error setting TTL");
			break;
		}

		struct timeval start, end;
		gettimeofday(&start, NULL);

		// Prepare ICMP header
		struct icmphdr icmp_hdr;
		icmp_hdr.type = ICMP_ECHO;
		icmp_hdr.code = 0;
		icmp_hdr.un.echo.id = htons(icmp_request_id);
		icmp_hdr.un.echo.sequence = htons(ttl);
		icmp_hdr.checksum = 0;
		icmp_hdr.checksum = icmp_checksum(&icmp_hdr, sizeof(icmp_hdr));

		if (sendto(sockfd, &icmp_hdr, sizeof(icmp_hdr), 0, (struct sockaddr *)dest_addr, sizeof(*dest_addr)) < 0)
		{
			perror("Error sending packet");
			break;
		}

		struct sockaddr_in sender_addr;
		socklen_t addr_len = sizeof(sender_addr);

		fd_set read_fds;
		FD_ZERO(&read_fds);
		FD_SET(sockfd, &read_fds);

		struct timeval timeout;
		timeout.tv_sec = 1;
		timeout.tv_usec = 0;

		int ready = select(sockfd + 1, &read_fds, NULL, NULL, &timeout);
		if (ready < 0)
		{
			perror("Error with select");
			break;
		}
		else if (ready == 0)
		{
			printf("%2d. * * *\n", ttl);
			continue;
		}

		// Buffer to receive the entire IP and ICMP headers
		char recv_buf[sizeof(struct iphdr) + sizeof(struct icmphdr)];
		ssize_t recv_len = recvfrom(sockfd, recv_buf, sizeof(recv_buf), 0, (struct sockaddr *)&sender_addr, &addr_len);
		if (recv_len < 0)
		{
			perror("Error receiving packet");
			break;
		}

		// Get the ICMP header from the received buffer
		struct icmphdr *recv_icmp = (struct icmphdr *)(recv_buf + sizeof(struct iphdr));

		// Check if the received ICMP ID matches our request
		// printf("recv_icmp->un.echo.id: %d && icmp_request_id %d\n", ntohs(recv_icmp->un.echo.id), icmp_request_id);
		// printf("sender_addr.sin_addr.s_addr %d && dest_addr->sin_addr.s_addr %d\n", sender_addr.sin_addr.s_addr, dest_addr->sin_addr.s_addr);
		gettimeofday(&end, NULL);
		print_result(&start, &end, &sender_addr);
		if (ntohs(recv_icmp->un.echo.id) != icmp_request_id)
		{
			continue;
		}

		if (sender_addr.sin_addr.s_addr == dest_addr->sin_addr.s_addr)
		{
			break;
		}
	}

	close(sockfd);
}

void print_result(struct timeval *start, struct timeval *end, struct sockaddr_in *sender_addr)
{
	long elapsed = (end->tv_sec - start->tv_sec) * 1000 + (end->tv_usec - start->tv_usec) / 1000;
	char ip_str[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &sender_addr->sin_addr, ip_str, INET_ADDRSTRLEN);
	printf("sender_addr->sin_port: %d\n", sender_addr->sin_port);
	printf("%2d. %s %ld ms\n", sender_addr->sin_port, ip_str, elapsed);
}

void clean_up(struct addrinfo *dest_info)
{
	freeaddrinfo(dest_info);
}
