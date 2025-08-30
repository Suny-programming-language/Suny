#ifndef SUNY_H
#define SUNY_H

#include <stdlib.h>
#include <stdio.h> 
#include <string.h>
#include <windows.h>
#include <stdint.h>

#include "opcode.h"

#define __iter__ "__iter__"
#define __iter__a 32

#define __i__ "__i__"
#define __i__a 33

#define SUNY_BREAK_POINT while(1)

#define SUNY_API __declspec(dllexport)

#define SUNY_LOCAL __declspec(dllimport)

typedef FARPROC Sdll_func;
typedef HMODULE Sdll_module;

#define __suny_lib__

#endif // SUNY_H