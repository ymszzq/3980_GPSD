#include <stdio.h>
#include <unistd.h>
#include <malloc.h>
#include <gps.h>

struct fixsource_t{
    char *spec; /* pointer to actual storage */
    char *server;
    char *port;
    char *device;
};