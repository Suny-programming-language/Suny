#include "suserdata.h"

struct Suserdata* Suserdata_new(void) {
    struct Suserdata* userdata = malloc(sizeof(struct Suserdata));
    userdata->data = NULL;
    userdata->type = NULL;
    return userdata;
}
struct Suserdata* Suserdata_set(void* data) {
    struct Suserdata* userdata = Suserdata_new();
    userdata->data = data;
    return userdata;
}

struct Sobj* Sobj_make_userdata(void* data) {
    struct Suserdata* userdata = Suserdata_set(data);
    struct Sobj* obj = Sobj_new();
    obj->type = USER_DATA_OBJ;
    obj->f_type = Stype_new();
    obj->f_type->f_userdata = userdata;
    return obj;
}

struct Suserdata* Suserdata_set_type(struct Suserdata* userdata, struct Stype* type) {
    userdata->type = type;
    return userdata;
}

int Suserdata_free(struct Suserdata* userdata) {
    free(userdata);
    return 0;
}