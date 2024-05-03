#include "../include/coordinateUtils.h"
#include <math.h>

double haversine(Coordinate client, Coordinate server){
    double deltaLatitude = (server.latitude - client.latitude) * M_PI/180.0;
    double deltaLongitude = (server.longitude - client.longitude) * M_PI/180.0;

    client.latitude = (client.latitude) * M_PI/180.0;
    server.latitude = (server.longitude) * M_PI/180.0;

    double ang = pow(sin(deltaLatitude/2),2) + pow(sin(deltaLongitude/2),2)* cos(client.latitude) * cos(server.latitude);
    double radius =  6371;
    double d = 2 * asin(sqrt(ang));
    return d * radius*10e2;
}