#include <stdio.h>
#include <string.h>

#include "Suny.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        prompt();
        return 1;
    }

    char* file_name = argv[1];

    SunyRunFile(file_name);
    
    return 0;
}