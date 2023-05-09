#include "ft_traceroute.h"
#include "libft.h"

void print_result(struct timeval round_trip[ROUND_TRIP_COUNT], struct sockaddr_in *sender_addr, int ttl)
{
	// long elapsed = (end->tv_sec - start->tv_sec) * 1000 + (end->tv_usec - start->tv_usec) / 1000;
	char ip_str[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &sender_addr->sin_addr, ip_str, INET_ADDRSTRLEN);
	// printf("sender_addr->sin_port: %d\n", sender_addr->sin_port);
	printf("%d  %s %.3fms", ttl, ip_str, (float)round_trip[0].tv_usec / 1000);
	printf(" %.3fms", (float)round_trip[1].tv_usec / 1000);
	printf(" %.3fms\n", (float)round_trip[2].tv_usec / 1000);
}

void clean_up()
{
	if (global_dest_info != NULL)
	{
		freeaddrinfo(global_dest_info);
		global_dest_info = NULL;
	}
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

void my_timersub(const struct timeval *a, const struct timeval *b, struct timeval *result)
{
	result->tv_sec = a->tv_sec - b->tv_sec;
	result->tv_usec = a->tv_usec - b->tv_usec;

	if (result->tv_usec < 0)
	{
		result->tv_sec -= 1;
		result->tv_usec += 1000000;
	}
}

void sigint_handler()
{
	if (global_dest_info != NULL)
	{
		freeaddrinfo(global_dest_info);
		global_dest_info = NULL;
	}
	ft_putstr_fd("\nft_traceroute: Interrupted by user\n", 2);
	exit(EXIT_FAILURE);
}