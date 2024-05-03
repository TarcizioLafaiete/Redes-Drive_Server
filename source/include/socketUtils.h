#ifndef __SOCKET_UTILS__
#define __SOCKET_UTILS__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define IPV4 0
#define IPV6 1
#define UNK 2

#define CLOSE_CLIENT (char)0xC1
#define REQUEST_DRIVE (char)0xC2
#define REQUEST_DRIVE_ACCEPTED (char)0xC3
#define REQUEST_DRIVE_REFUSED (char)0xC4
#define ACKNOWLEDGE_REQ (char)0xC5
#define DRIVE_FINISH_REQ (char) 0xEF

typedef struct{
    int type;
} typeIP;

typedef struct{
    struct sockaddr_in addr;
    struct sockaddr_in6 addr6;
    socklen_t len;
} socket_address;


typeIP translateIP(char* ip);
socket_address configure_addr(typeIP inet, int port);
void create_socket(int* socket_fd,typeIP inet);

const char* receiveMessage(int socket);
void sendMessage(const char* msg,int socket);

#endif