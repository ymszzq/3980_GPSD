#include <stdio.h>
#include <unistd.h>
#include <malloc.h>
#include <gps.h>

#define LOCAL_HOST = "127.0.0.1"

struct fixsource_t{
    char *spec; /* pointer to actual storage */
    char *server;
    char *port;
    char *device;
};