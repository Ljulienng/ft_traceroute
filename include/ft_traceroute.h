#ifndef TRACEROUTE_H
#define TRACEROUTE_H

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

#define MAX_HOPS 64
#define ROUND_TRIP_COUNT 3

typedef struct s_info
{
	int sockfd;
	socklen_t addr_len;
	struct sockaddr_in *dest_addr;
	struct sockaddr_in sender_addr;
	struct icmphdr icmp_hdr;
} t_info;

// Function declarations
void print_help();
int process_arguments(int argc, char **argv, char **destination);
struct addrinfo *resolve_destination(char *destination);
void perform_traceroute(struct addrinfo *dest_info);
void print_result(struct timeval round_trip[ROUND_TRIP_COUNT], struct sockaddr_in *sender_addr, int ttl);
void clean_up(struct addrinfo *dest_info);
ssize_t request_loop(t_info info, int ttl, struct timeval round_trip[ROUND_TRIP_COUNT]);
uint16_t icmp_checksum(const void *data, size_t len);
void my_timersub(const struct timeval *a, const struct timeval *b, struct timeval *result);

#endif