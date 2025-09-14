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

struct Sframe* Sframe_register_userdata(struct Sframe* frame, struct Scompiler* compiler, void* data, int address, char* name, char* doc) {
    struct Sobj* obj = Sobj_make_userdata(data);
    Sframe_store_global(frame, address, obj, USER_DATA_OBJ);
    add_scope(compiler, name, address, 0);
    return frame;
}