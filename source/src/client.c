#include <stdlib.h>
#include <stdio.h>

#include "../include/socketUtils.h"
#include "../include/clientCore.h"
#include "../include/terminalPrinter.h"
#include "../include/coordinateUtils.h"

Coordinate coordClient = {.latitude = -19.7884, .longitude = -42.01325};


int initClient(char* argv[]){
    clientCore core;

    core.inet = translateIP(argv[1]);

    create_socket(&core.client_fd,core.inet);
    core.serverSocket = configure_addr(core.inet,atoi(argv[3]));
    inet_pton(AF_INET,argv[2],&core.serverSocket.addr.sin_addr);
    
    connect_client(&core);

    return core.client_fd;
}

int acceptRequest(int socketClient){
    int request;
    
    printf("Solicitacao de corrida: ");
    scanf("%d",&request);
    printf("request: %d \n",request);
    if(!request){
        // close_client(socketClient);
        printf("here \n");
        return -1;     
    }
    else if(request != 1){
        printf("Opcao invalida, digite apenas 0 e 1 \n");
        return 1;
    }
    return 0;

}

int acceptProcess(int socketClient){
    printAcceptRide();
    int rideAcceptLoop = 1;
    while(rideAcceptLoop){
        int accept = acceptRequest(socketClient);
        printf("accept: %d \n",accept);
        if(accept == -1){
            printf("here 2 \n");
            return 0;
        }
        else if(accept == 0){
            rideAcceptLoop = 0; 
        }
    }
    return 1;
}

void sendClientCoordinate(int socket){
    char latitude[16];
    char longitude[16];

    sprintf(latitude,"%lf",coordClient.latitude);
    sprintf(longitude,"%lf",coordClient.longitude);

    sendMessage(latitude,socket);
    receiveMessage(socket);
    sendMessage(longitude,socket);
}

void driveRoutine(int socket){
    printInitOrEndDrive();
    char c = ACKNOWLEDGE_REQ;
    while(1){
        const char* recv = receiveMessage(socket);
        if(recv[0] == DRIVE_FINISH_REQ){
            printInitOrEndDrive();
            return;
        }
        sendMessage(&c,socket);
        printUpdateDistance(recv);
    }
}

int main(int argc, char* argv[]){
    int socketClient = initClient(argv);

    int mainClientLoop = 1;
    while(mainClientLoop){
        
        int acceptResult = acceptProcess(socketClient);
        printf("accept Result: %d \n",acceptResult);
        if(acceptResult == 0){
            printf("here 3 \n");
            close_client(socketClient);
            printEndOfRide();
            return 0;
        }

        char c = REQUEST_DRIVE;
        sendMessage(&c,socketClient);
        const char* response = receiveMessage(socketClient);
        if(response[0] == REQUEST_DRIVE_ACCEPTED){
            mainClientLoop = 0;
            sendClientCoordinate(socketClient);
            break;
        }
        else{
            printNotFoundDrive();
        }
    }

    
    driveRoutine(socketClient);


    close_client(socketClient);

    printEndOfRide();

    return 0;
}

