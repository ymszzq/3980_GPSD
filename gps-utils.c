/*------------------------------------------------------------------------------------------------------------------
--SOURCE FILE : gps-utils.c 
-- This file contains functions to read data from the gps device and handle any errors that occur.
--
--PROGRAM : dcgps
--
--FUNCTIONS :
	-- void read_gps(struct gps_data_t* gpsdata)
	-- void cleanup(int code, struct gps_data_t* gpsdata)
	--
	--DATE: November 6, 2018
	--
	--
	--DESIGNER : Wayne Huang
	--
	--PROGRAMMER : Wayne Huang
	--
	--NOTES :
	-- The program will call on the read data function to store the gps data into the gps_data_t structure. Then this
	-- will be passed to the print function in another file.
	--
	-- If any errors occur, the error checking function will determine what the error is based on the error code and
	-- then print relevant information and terminate the program.
	--
----------------------------------------------------------------------------------------------------------------------*/
#include "gps-utils.h"

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: read_gps
--
-- DATE: November 6, 2018
--
-- DESIGNER: Wayne Huang
--
-- PROGRAMMER: Wayne Huang
--
-- INTERFACE: void read_gps(struct gps_data_t* gpsdata)
--
-- RETURNS: void
--
-- NOTES:
-- Reads from the gps and puts the data in gpsdata, then calls the gps print function.
----------------------------------------------------------------------------------------------------------------------*/
void read_gps(struct gps_data_t* gpsdata) {
	int timeoutCount = 0;
	while(true) {
		/* set timeout to be 1 second (1000000 micro seconds)*/
		if (!gps_waiting(gpsdata, 1000000)) {
			if (timeoutCount >= 10) {
				/* if device has not responded for 10 timeouts terminate program 
				   with GPS_TIMEOUT error code*/
				cleanup(GPS_TIMEOUT, gpsdata);
			}
			timeoutCount++;
		}
		else {
			timeoutCount = 0;
			errno = 0;
			if (gps_read(gpsdata) == -1) {
				/* failed to read data from gps error handling */
				fprintf(stderr, "Fail to get data \n");
				cleanup (errno == 0 ? GPS_GONE : GPS_ERROR, gpsdata);
			}
			else {
				/* passes gps data to the gps print function */
				printGps(gpsdata);
			}
		}
	}
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: cleanup
--
-- DATE: November 6, 2018
--
-- DESIGNER: Wayne Huang
--
-- PROGRAMMER: Wayne Huang
--
-- INTERFACE: cleanup(int code, struct gps_data_t* gpsdata)
--
-- RETURNS: void
--
-- NOTES:
-- The error handling for non-functioning gps states. Will log the type of error and terminate the program.
----------------------------------------------------------------------------------------------------------------------*/
void cleanup(int code, struct gps_data_t* gpsdata) {
	gps_stream(gpsdata, WATCH_DISABLE, NULL);
	gps_close(gpsdata);

	switch (code) {
	case GPS_QUIT:
		break;
	case GPS_GONE:
		fprintf(stderr, "GPS unresponsive \n");
		break;
	case GPS_ERROR:
		fprintf(stderr, "GPS had error reading \n");
		break;
	case GPS_TIMEOUT:
		fprintf(stderr, "GPS timed out \n");
		break;
	default:
		break;
	}

	exit(0);
}