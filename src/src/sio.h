#ifndef SIO_H
#define SIO_H

#include "score.h"
#include "sobj.h"

struct Sobj;

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int Sio_write(struct Sobj *obj);

#endif