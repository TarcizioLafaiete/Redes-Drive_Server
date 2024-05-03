#include <stdlib.h>
#include <stdio.h>

#include "../include/socketUtils.h"
#include "../include/serverCore.h"
#include "../include/terminalPrinter.h"
#include "../include/coordinateUtils.h"

Coordinate coordServ = {-19.9227,-43.9451};



int* initServer(char* argv[]){
    serverCore core;

    core.inet = translateIP(argv[1]);

    create_socket(&core.server_fd,core.inet);
    core.socket = configure_addr(core.inet,atoi(argv[2]));
    configure_options(core.server_fd);
    binding(&core);
    listening(core.server_fd);

    printWaitingRequest();
    
    int conn_sock = acceptConnection(&core);
    if(conn_sock < 0){
        printf("Sem conexao no aceita \n");
        exit(EXIT_FAILURE);
    }

    int* fd = (int*)malloc(sizeof(int) * 2);
    fd[0] = core.server_fd;
    fd[1] = conn_sock;

    return fd;
}

int acceptDrive(int* socket){
    int request;

    while(1){
        printRideAvaiable();
        printf("Aceitar? ");

        scanf("%d",&request);

        if(request != 0 && request != 1){
            printf("Opcao invalida, digite apenas 0 e 1 \n");            
        }
        else{
            char req = 0;
            if(request == 1){
                req = REQUEST_DRIVE_ACCEPTED;
            }
            else{
                req = REQUEST_DRIVE_REFUSED;
            }
            sendMessage(&req,socket[1]);
            return request;
        }
    }

}

Coordinate recvClientCoordinate(int* socket){
    Coordinate clientCoord;
    char c = ACKNOWLEDGE_REQ;
    const char* latitude = receiveMessage(socket[1]);
    clientCoord.latitude = strtod(latitude,NULL);
    sendMessage(&c,socket[1]);

    const char* longitude = receiveMessage(socket[1]);
    clientCoord.longitude = strtod(longitude,NULL);
    
    return clientCoord;
}

void updateDistance(int* socket,double distance){
    char message[50];
    char c = DRIVE_FINISH_REQ;
    while(distance > 400){
        sprintf(message,"Motorista a %.2lf m \n",distance);
        sendMessage(message,socket[1]);
        receiveMessage(socket[1]);
        distance -= 400;
        sleep(2);
    }
    sendMessage("O Motorista chegou!",socket[1]);
    printInitOrEndDrive();
    printUpdateDistance("O Motorista chegou!");
    printInitOrEndDrive();
    receiveMessage(socket[1]);
    sendMessage(&c,socket[1]);
}

int main(int argc,char* argv[]){

    int* sock = initServer(argv);

    while(1){
        const char* firstRequest = receiveMessage(sock[1]);
        if(firstRequest[0] == CLOSE_CLIENT){
            close_server(sock[0],sock[1]);
            sock = initServer(argv);
        }
        else{
            int drive_situation = acceptDrive(sock);
            if(!drive_situation){
                printWaitingRequest();
            }
            else{
                Coordinate coordClient = recvClientCoordinate(sock);
                double distance = haversine(coordClient,coordServ);
                updateDistance(sock,distance);
            }
        }
    }

    return 0;
}