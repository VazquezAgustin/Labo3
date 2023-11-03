#ifndef _CLAVE_H
#define _CLAVE_H

#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>

key_t creo_clave(int r_clave);

#endif
