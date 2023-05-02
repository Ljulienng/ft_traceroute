#include "ft_traceroute.h"
#include "libft.h"

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("traceroute: missing host operand\n Try 'traceroute --help' for more information \n");
		return 1;
	}

	int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sockfd < 0)
	{
		printf("socket error\n");
		return 1;
	}

	struct timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 0;
	if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0)
	{
		printf("setsockopt error\n");
		return 1;
	}

	struct addrinfo hints, *res;
	int status;

	ft_memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;

	if ((status = getaddrinfo(argv[1], NULL, &hints, &res)) != 0)
	{
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
		return 1;
	}

	t_hop hops[MAX_HOPS];
	int tt1 = 1;
	int done = 0;
	while (tt1 < MAX_HOPS && !done)
	{
		setsockopt(sockfd, IPPROTO_IP, IP_TTL, &tt1, sizeof(int));

		char packet[PACKET_SIZE];
		ft_memset(packet, 0, PACKET_SIZE);
		packet[0] = tt1;
		packet[1] = 0;
		packet[2] = 0;
		packet[3] = 0;
		socklen_t len = sizeof(struct sockaddr_in);
		sendto(sockfd, packet, PACKET_SIZE, 0, res->ai_addr, len);)
	}
}
