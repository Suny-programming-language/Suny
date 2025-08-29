#include "sbuff.h"

struct SZIO*
Sbuff_new(void) {
    struct SZIO *zio = malloc(sizeof(struct SZIO));

    zio->file = "stdin";
    zio->buffer = NULL;
    zio->size = 0;

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