#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <arpa/inet.h>
#include <errno.h>
#include "utils.h"

#define ETH_NAME        "eth0"

char *get_local_addr()
{
        int sock;
	char *ip_addr = NULL;
        struct sockaddr_in sin;
        struct ifreq ifr;

        sock = socket(AF_INET, SOCK_DGRAM, 0);
        if (sock == -1)
        {
                perror("socket");
                return NULL;
        }

        strncpy(ifr.ifr_name, ETH_NAME, IFNAMSIZ);
        ifr.ifr_name[IFNAMSIZ - 1] = 0;
        if (ioctl(sock, SIOCGIFADDR, &ifr) < 0)
        { 
                perror("ioctl");
                return NULL;
        }
        memcpy(&sin, &ifr.ifr_addr, sizeof(sin));
        ip_addr = inet_ntoa(sin.sin_addr);
        return ip_addr;
}
