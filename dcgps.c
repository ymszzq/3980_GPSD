/*-------------------------------------------------------------------------------------------------------------------- SOURCE FILE: dgps.c - An application that will constantly retrieve data from gps device by using GPSD C library,--                       and print it in format. ---- PROGRAM: gpsTerminal---- FUNCTIONS:int main() ------ DATE: November 03, 2018------ DESIGNER: Ziqian Zhang---- PROGRAMMER: Ziqian Zhang---- NOTES:-- This file is the entry point for the whole program. This program sets up the connection to GPSD daemon, start reading loop.-- It will also do cleanup operations when the application terminates.----------------------------------------------------------------------------------------------------------------------*/#include "gps-utils.h"#include "dcgps.h"static struct fixsource_t source;static struct gps_data_t gpsdata;/*-------------------------------------------------------------------------------------------------------------------- FUNCTION: int main()---- DATE: November 03, 2018------ DESIGNER: Ziqian Zhang---- PROGRAMMER: Ziqian Zhang---- INTERFACE: int main()---- RETURNS: return 0 if program terminate.---- NOTES:-- This function is the entry point for the whole program. This program allocate the memery for  gps_data_t structure,-- initilize source struct, open the stream to gpsd, set the flag, start the stream. It will also do cleanup operations-- when the application terminates.----------------------------------------------------------------------------------------------------------------------*/int main(){    struct gps_data_t* gpsdata_prt  = malloc(sizeof(struct gps_data_t));    gpsdata_prt = &gpsdata;    unsigned int flags = WATCH_ENABLE;    /*Initialize server address with localhost, port with default port*/    source.server = LOCAL_HOST;    source.port = DEFAULT_GPSD_PORT;    source.device = NULL;    /*Open the stream*/    if(gps_open(source.server,source.port,&gpsdata)!=0){        printf("connection fail\n");    }    if(source.device!=NULL)        flags |= WATCH_DEVICE;    (void) gps_stream(&gpsdata, flags, source.device);    /*Enter read loop*/    read_gps(gpsdata_prt);    /*Clean and free stream and memery before program terminated*/    gps_stream(gpsdata_prt, WATCH_DISABLE, NULL);	gps_close(gpsdata_prt);    return 0;}