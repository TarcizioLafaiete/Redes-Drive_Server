#ifndef __CLIENT_CORE__
#define __CLIENT_CORE__

#include "socketUtils.h"

typedef struct{
    int client_fd;
    socket_address serverSocket;
    typeIP inet;
} clientCore;

void connect_client(clientCore* core);
void close_client(int socket);

#endif