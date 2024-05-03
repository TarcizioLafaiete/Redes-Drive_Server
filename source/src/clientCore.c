#include "../include/clientCore.h"
#include "../include/socketUtils.h"

void connect_client(clientCore* core){
    int status = 0;
    if(core->inet.type == IPV4){
        status = connect(core->client_fd,(struct sockaddr*)&core->serverSocket.addr,sizeof(core->serverSocket.addr));
    }
    else if(core->inet.type == IPV6){
        status = connect(core->client_fd,(struct sockaddr*)&core->serverSocket.addr6,sizeof(core->serverSocket.addr6));
    }

    if(status < 0){
        printf("Falha de conexao \n");
        exit(EXIT_FAILURE);
    }

}

void close_client(int socket){
    char c = CLOSE_CLIENT;
    sendMessage(&c,socket);
    close(socket);
}