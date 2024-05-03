#ifndef __SERVER_CORE__
#define __SERVER_CORE__

#include "socketUtils.h"


typedef struct{
    int server_fd;
    socket_address socket;
    typeIP inet;
} serverCore;

void configure_options(int server_fd);
void binding(serverCore* core);
void listening(int server_fd);
int acceptConnection(serverCore* core);
void close_server(int socket_fd, int conn_sock);

#endif