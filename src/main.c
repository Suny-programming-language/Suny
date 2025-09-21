#include <stdio.h>
#include <string.h>

#include "Suny.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        prompt();
        return 1;
    }

    char* file_name = argv[1];

    if (same_string(file_name, "-c")) {
        file_name = argv[2];
        compilefile(file_name);
        return 0;
    }

    if (same_string(file_name, "-p")) {
        prompt();
        return 0;
    }

    if (same_string(file_name, "-h")) {
        printf("Suny 1.0 Copyright (C) 2025-present, by dinhsonhai132\n");
        printf("Usage: suny [options] [file]\n");
        printf("Options:\n");
        printf("  -c [file] Compile the file\n");
        printf("  -p Run the prompt\n");
        printf("  -h Show this help\n");
        return 0;
    }

    if (same_string(file_name, "-v")) {
        printf("Suny 1.0 Copyright (C) 2025-present, by dinhsonhai132\n");
        return 0;
    }

    SunyRunFile(file_name);
    
    return 0;
}