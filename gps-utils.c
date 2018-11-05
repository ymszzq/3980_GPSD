#include "gps-utils.h"

void read_gps(struct gps_data_t* gpsdata) {
	int timeoutCount = 0;
	while(true) {
		if (!gps_waiting(gpsdata, 1000000)) {
			if (timeoutCount >= 10) {
				cleanup(GPS_TIMEOUT, gpsdata);
			}
			timeoutCount++;
		}
		else {
			timeoutCount = 0;
			errno = 0;
			if (gps_read(gpsdata) == -1) {
				fprintf(stderr, "Fail to get data \n");
				cleanup (errno == 0 ? GPS_GONE : GPS_ERROR, gpsdata);
			}
			else {
				printGps(gpsdata);
			}
		}
	}
}

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