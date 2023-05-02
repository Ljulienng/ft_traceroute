#ifndef TRACEROUTE_H
#define TRACEROUTE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netdb.h>
#include <sys/time.h>

#define MAX_HOPS 64
#define MAX_PACKET_SIZE 60

typedef struct s_hop
{
	char *ip;
	double rtt;
} t_hop;

#endif