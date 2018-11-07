#ifndef _GPS_UTILS_H
#define _GPS_UTILS_H

#include <gps.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "gpsprint.h"

#define GPS_QUIT	0	
#define GPS_GONE	-1	
#define GPS_ERROR	-2	
#define GPS_TIMEOUT	-3	

void read_gps(struct gps_data_t*);
void error_process(int);

#endif