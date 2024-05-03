#ifndef __CORDINATEUTILS_H__
#define __CORDINATEUTILS_H__

#include <math.h>

typedef struct {
    double latitude;
    double longitude;
} Coordinate;


double haversine(Coordinate client, Coordinate server);

#endif