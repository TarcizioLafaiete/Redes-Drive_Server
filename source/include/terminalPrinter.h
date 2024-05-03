#ifndef __TERMINALPRINTER_H__
#define __TERMINALPRINTER_H__

#include <stdlib.h>
#include <stdio.h>

void printWaitingRequest();
void printRideAvaiable();
void printAcceptRide();
void printNotFoundDrive();
void printInitOrEndDrive();
void printUpdateDistance(const char* message);
void printEndOfRide();

#endif