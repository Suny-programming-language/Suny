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
Sadd_1_char(char c1) {
    char* buffer = (char*) malloc(sizeof(char) * 1);
    buffer[0] = c1;
    buffer[1] = '\0';
    return buffer;
}

char*
Sadd_2_char(char c1, char c2) {
    char* buffer = (char*) malloc(sizeof(char) * 3);
    buffer[0] = c1;
    buffer[1] = c2;
    buffer[2] = '\0';
    return buffer;
}

char*
Sadd_3_char(char c1, char c2, char c3) {
    char* buffer = (char*) malloc(sizeof(char) * 4);
    buffer[0] = c1;
    buffer[1] = c2;
    buffer[2] = c3;
    buffer[3] = '\0';
    return buffer;
}

char*
Sadd_4_char(char c1, char c2, char c3, char c4) {
    char* buffer = (char*) malloc(sizeof(char) * 5);
    buffer[0] = c1;
    buffer[1] = c2;
    buffer[2] = c3;
    buffer[3] = c4;
    buffer[4] = '\0';
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

int
Sisdigit(char chr) {
    if (chr >= '0' && chr <= '9') return 1;
    return 0;
}

int
Sisstrdigit(char *str) {
    int dot_count = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];

        if (c == '.') {
            dot_count++;
            if (dot_count > 1) return 0;
        } else if (!Sisdigit(c)) {
            return 0;
        }
    }

    return 1;
}

char* Sstring_new(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    va_list args_copy;
    va_copy(args_copy, args);
    int len = vsnprintf(NULL, 0, fmt, args_copy);
    va_end(args_copy);

    if (len < 0) {
        va_end(args);
        return NULL;
    }

    char* buf = (char*)malloc(len + 1);
    if (!buf) {
        va_end(args);
        return NULL;
    }

    vsnprintf(buf, len + 1, fmt, args);
    va_end(args);

    return buf;
}

char* remove_substr(char* str, const char* to_remove) {
    if (!str || !to_remove) return str;

    size_t len_str = strlen(str);
    size_t len_rem = strlen(to_remove);
    if (len_rem == 0) return str;

    char* result = malloc(len_str + 1);
    if (!result) return NULL;

    char* p = str;
    char* r = result;

    while (*p) {
        if (strncmp(p, to_remove, len_rem) == 0) {
            p += len_rem;
        } else {
            *r++ = *p++;
        }
    }

    *r = '\0';
    return result;
}

int if_file_exists(const char* filename) {
    struct stat buffer;
    return (stat(filename, &buffer) == 0 && S_ISREG(buffer.st_mode));
}

int if_file_exists_in(const char* filename, const char* path) {
    if (!filename || !path) return 0;

    size_t len = strlen(filename) + strlen(path) + 2;
    char *fullpath = malloc(len);
    if (!fullpath) return 0;

    snprintf(fullpath, len, "%s/%s", path, filename);
    int exists = if_file_exists(fullpath);
    free(fullpath);

    return exists;
}

int if_folder_exists(const char* foldername) {
    struct stat buffer;
    return (stat(foldername, &buffer) == 0 && S_ISDIR(buffer.st_mode));
}

int if_folder_exists_in(const char* foldername, const char* path) {
    if (!foldername || !path) return 0;

    size_t len = strlen(foldername) + strlen(path) + 2;
    char *fullpath = malloc(len);
    if (!fullpath) return 0;

    snprintf(fullpath, len, "%s/%s", path, foldername);
    int exists = if_folder_exists(fullpath);
    free(fullpath);

    return exists;
}
