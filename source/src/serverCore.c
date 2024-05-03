#include "../include/serverCore.h"

void configure_options(int server_fd){
    int opt = 1;
    int setop = setsockopt(server_fd,SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT,&opt,sizeof(opt));
    if(setop < 0){
        printf("Configuracao falhou \n");
        exit(EXIT_FAILURE);
    }
}

void binding(serverCore* core){

    int bind_fd = -1;
    if(core->inet.type == IPV4){
        bind_fd = bind(core->server_fd,(struct sockaddr*)&core->socket.addr,sizeof(core->socket.addr));
    }
    else if(core->inet.type == IPV6){
        bind_fd = bind(core->server_fd,(struct sockaddr*)&core->socket.addr6,sizeof(core->socket.addr6));
    }

    if(bind_fd < 0){
        printf("Processo de binding nao funcionou \n");
        exit(EXIT_FAILURE);
    }

}

void listening(int server_fd){
    int listen_fd = listen(server_fd,3);
    if(listen_fd < 0){
        printf("Nao foi possivel abrir a escuta \n");
        exit(EXIT_FAILURE);
    }
}

int acceptConnection(serverCore* core){
    if(core->inet.type == IPV4){
        return accept(core->server_fd,(struct sockaddr*)&core->socket.addr,&core->socket.len);
    }
    else if(core->inet.type == IPV6){
        return accept(core->server_fd,(struct sockaddr*)&core->socket.addr6,&core->socket.len);
    }
    else{
        return -1;
    }
}

void close_server(int socket_fd, int conn_sock){
    close(conn_sock);
    close(socket_fd);
}
