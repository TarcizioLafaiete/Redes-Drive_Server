#include "../include/terminalPrinter.h"

void printWaitingRequest(){
    printf("|------------------------------ | \n");
    printf("| Aguardando a solicitacao      | \n");
    printf("|-------------------------------| \n");
}

void printRideAvaiable(){
    printf("|------------------------------ | \n");
    printf("| Corrida disponivel            | \n");
    printf("| 0 - Recusar                   | \n");
    printf("| 1 - Aceitar                   | \n");
    printf("|------------------------------ | \n");
}

void printAcceptRide(){
    printf("|------------------------------ | \n");
    printf("| 0 - Sair                      | \n");
    printf("| 1 - Solicitar Corrida         | \n");
    printf("|                               | \n");
    printf("|------------------------------ | \n");
}

void printNotFoundDrive(){
    printf("|------------------------------ | \n");
    printf("| Nao foi encontrado um         | \n");
    printf("| motorista                     | \n");
    printf("|------------------------------ | \n");
}

void printInitOrEndDrive(){
    printf("|------------------------------ | \n");
}

void printUpdateDistance(const char* message){
    printf("| %s       | \n",message);
}

void printEndOfRide(){
    printf("|      <Programa encerrado>      |\n");
}