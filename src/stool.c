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


int
Scharcmp_bigger(char *a, char *b, int size_a, int size_b) {
    int min = size_a < size_b ? size_a : size_b;

    for (int i = 0; i < min; i++) {
        if (a[i] > b[i]) return 1; 
        if (a[i] < b[i]) return 0; 
    }

    return size_a > size_b;
}

int
Scharcmp_smaller(char *a, char *b, int size_a, int size_b) {
    int min = size_a < size_b ? size_a : size_b;

    for (int i = 0; i < min; i++) {
        if (a[i] < b[i]) return 1; 
        if (a[i] > b[i]) return 0; 
    }
    return size_a < size_b;
}

int
Scharcmp_equal(char *a, char *b, int size_a, int size_b) {
    if (size_a != size_b) return 0;

    for (int i = 0; i < size_a; i++) {
        if (a[i] != b[i]) {
            return 0;
        }
    }
    
    return 1;
}

char*
Sadd_2_char(char c1, char c2) {
    char* buffer = (char*) malloc(sizeof(char) * 2);
    buffer[0] = c1;
    buffer[1] = c2;
    return buffer;
}

char*
Sadd_3_char(char c1, char c2, char c3) {
    char* buffer = (char*) malloc(sizeof(char) * 3);
    buffer[0] = c1;
    buffer[1] = c2;
    buffer[2] = c3;
    return buffer;
}

char*
Sadd_4_char(char c1, char c2, char c3, char c4) {
    char* buffer = (char*) malloc(sizeof(char) * 4);
    buffer[0] = c1;
    buffer[1] = c2;
    buffer[2] = c3;
    buffer[3] = c4;
    return buffer;
}

int
Slen(char *str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

Sdll_func dll_get_func(char* func_name, char* dll_name) {
    Sdll_module hModule = LoadLibrary(dll_name);

    if (!hModule) {
        printf("Failed to load %s\n", dll_name);
        return NULL;
    }

    Sdll_func func = GetProcAddress(hModule, func_name);

    if (!func) {
        printf("Failed to get %s from %s\n", func_name, dll_name);
        return NULL;
    }

    return func;
}