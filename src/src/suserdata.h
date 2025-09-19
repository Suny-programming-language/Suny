#ifndef SUSERDATA_H
#define SUSERDATA_H

#include "sobj.h"
#include "scompile.h"
#include "sframe.h"

struct Stype;
struct Scompiler;

#define get_userdata(obj) (obj->f_type->f_userdata->data)

struct Suserdata* 
Suserdata_new(void);

struct Suserdata* 
Suserdata_set
(void* data);

struct Suserdata* 
Suserdata_set_type
(struct Suserdata* userdata, struct Stype* type);

struct Sobj* 
Sobj_make_userdata
(void* data);

struct Sframe* 
Sframe_register_userdata
(struct Sframe* frame, struct Scompiler* compiler, void* data, int address, char* name, char* doc);

int Suserdata_free(struct Suserdata* userdata);

#endif  // SUSERDATA_H