#include "stool.h"

__suny_lib__ double 
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

__suny_lib__ char* 
Sto_char(char chr[], int len) {
    char* new_char = malloc(sizeof(char) * (len + 1));
    strcpy(new_char, chr);
    return new_char;
}