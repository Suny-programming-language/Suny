#include "stool.h"

double 
Satof(const char *str) {
    double result = 0.0;
    double frac = 0.0;
    int sign = 1;
    int i = 0;

    while (str[i] == ' ' || str[i] == '\t') {
        i++;
    }

    if (str[i] == '-') {
        sign = -1;
        i++;
    } else if (str[i] == '+') {
        i++;
    }

    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    if (str[i] == '.') {
        i++;
        double base = 0.1;
        while (str[i] >= '0' && str[i] <= '9') {
            frac += (str[i] - '0') * base;
            base *= 0.1;
            i++;
        }
    }

    return sign * (result + frac);
}

char* 
Sto_char(char chr[], int len) {
    char* new_char = malloc(sizeof(char) * (len + 1));
    strcpy(new_char, chr);
    return new_char;
}


int 
Stoi(const char *str) {
    int result = 0;
    int sign = 1;
    int i = 0;

    while (str[i] == ' ' || str[i] == '\t') {
        i++;
    }

    if (str[i] == '-') {
        sign = -1;
        i++;
    } else if (str[i] == '+') {
        i++;
    }

    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    return sign * result;
}

void 
Sreverse(void **array, int size) {
    int start = 0;
    int end = size - 1;

    while (start < end) {
        void *tmp = array[start];
        array[start] = array[end];
        array[end] = tmp;
        start++;
        end--;
    }
}

char*
Sftchr(float value) {
    char* buffer = (char*) malloc(sizeof(char) * 32);
    sprintf(buffer, "%f", value);



    return buffer;
}

char
Sgchrfromf(float value, int index) {
    // Sgchrfromf(400, 0) -> 4
    // Sgchrfromf(400, 1) -> 0
    // Sgchrfromf(400, 2) -> 0
    // Sgchrfromf(400, 3) -> out of range

    char* buffer = (char*) malloc(sizeof(char) * 32);
    sprintf(buffer, "%f", value);
    if (index >= strlen(buffer)) {
        printf("Index out of range\n");
        return '\0';
    };
    return buffer[index];
}