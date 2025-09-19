#ifndef SCORE_H
#define SCORE_H

#define SUNY_VERSION "1.0"
#define SUNY_COPYRIGHT "Copyright (c) 2025-present dinhsonhai132"
#define AUTHOR "dinhsonhai132"

#define SUNY_LIB_PATH "C:\\Suny\\Suny\\libs\\"
#define PATH_TO_DLL_LIB "C:\\Suny\\Suny\\libs\\%s.dll"

#ifdef _WIN32
    #include <windows.h>
    #define PATH_TO_SUNY_LIB_WINDOW "C:\\Suny\\libs\\"

    typedef FARPROC Sdll_func;
    typedef HMODULE Sdll_module;

    #define SUNY_API   __declspec(dllexport)
    #define SUNY_LOCAL __declspec(dllimport)

#else
    #warning "This library is currently only supported on Windows!"
    typedef void* Sdll_func;
    typedef void* Sdll_module;
    #define SUNY_API
    #define SUNY_LOCAL
#endif

#define __iter__ "__iter__"
#define __iter__a 32

#define __i__ "__i__"
#define __i__a 33

#define SUNY_BREAK_POINT while(1)

#define __suny_lib__

#include "opcode.h"
#include "max.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>   
#include <stdint.h>

#endif // SCORE_H
