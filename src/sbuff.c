#include "sbuff.h"
#include <dirent.h>

struct SZIO*
Sbuff_new(void) {
    struct SZIO *zio = malloc(sizeof(struct SZIO));

    zio->file = "stdin";
    zio->buffer = NULL;
    zio->size = 0;

    zio->nf = 0;
    zio->maxf = 100;
    zio->folders = calloc(zio->maxf, sizeof(char*));

    return zio;    
}

int 
Sbuff_free
(struct SZIO *zio) {
    if (!zio) return 0;
    free(zio->buffer);
    free(zio);

    return 1;
}

struct SZIO*
Sbuff_read_file
(char* file) {
    if (!file) return NULL;

    FILE *fp = fopen(file, "rb");
    if (!fp) {
        perror("fopen");
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    rewind(fp);

    struct SZIO *zio = Sbuff_new();
    if (!zio) {
        fclose(fp);
        return NULL;
    }

    zio->file = file;
    zio->buffer = (char*)malloc(fsize + 1);
    if (!zio->buffer) {
        free(zio);
        fclose(fp);
        return NULL;
    }

    size_t nread = fread(zio->buffer, 1, fsize, fp);
    fclose(fp);

    zio->buffer[nread] = '\0';
    zio->size = (int)nread;

    return zio;
}

struct SZIO* 
Sbuff_write_bytecode_file(unsigned char* content, size_t size, const char* filename) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) return NULL;

    size_t written = fwrite(content, 1, size, fp);
    fclose(fp);

    if (written != size) {
        return NULL; 
    }

    struct SZIO *zio = malloc(sizeof(struct SZIO));
    if (!zio) return NULL;

    zio->file = strdup(filename); 
    zio->buffer = malloc(size);
    if (!zio->buffer) {
        free(zio->file);
        free(zio);
        return NULL;
    }

    memcpy(zio->buffer, content, size);
    zio->size = size;

    return zio;
}

struct SZIO*
Sbuff_read_folder_name(char* path) {
    if (!path) return NULL;

    DIR *dir = opendir(path);
    if (!dir) {
        perror("opendir");
        return NULL;
    }

    struct dirent *entry;
    struct SZIO *zio = Sbuff_new();

    zio->file = strdup(path);
    zio->folders = NULL;
    zio->nf = 0;
    zio->maxf = 0;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        if (zio->nf >= zio->maxf) {
            zio->maxf = (zio->maxf == 0) ? 8 : zio->maxf * 2;
            zio->folders = realloc(zio->folders, zio->maxf * sizeof(char*));
        }

        zio->folders[zio->nf] = strdup(entry->d_name); // lưu tên file/folder
        zio->nf++;
    }

    closedir(dir);
    return zio;
}

struct SZIO*
Sbuff_find_file_in(char* filename, char* path) {
    if (!filename || !path) return NULL;

    DIR *dir = opendir(path);
    if (!dir) {
        perror("opendir");
        return NULL;
    }

    struct dirent *entry;
    struct SZIO *zio = NULL;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        if (strcmp(entry->d_name, filename) == 0) {
            zio = Sbuff_new();
            zio->file = strdup(entry->d_name);

            size_t len = strlen(path) + strlen(entry->d_name) + 2;
            char *fullpath = malloc(len);
            snprintf(fullpath, len, "%s/%s", path, entry->d_name);
            zio->buffer = strdup(fullpath);
            zio->size = 0;

            free(fullpath);
            break;
        }
    }

    closedir(dir);
    return zio;
}