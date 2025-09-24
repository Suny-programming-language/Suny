#include "C:/Suny/Suny.h"
#include "SGL.h"

struct Sobj* Sobj_plus_square(struct Sobj* obj1, struct Sobj* obj2) {
    SDL_Rect *rect1 = get_userdata(obj1);
    SDL_Rect *rect2 = get_userdata(obj2);

    SDL_Rect *rect3 = Screat_rect(rect1->x + rect2->x, rect1->y + rect2->y, rect1->w + rect2->w, rect1->h + rect2->h);

    struct Sobj* userdata = Sobj_make_userdata(rect3);

    return userdata;
}

struct Sobj* Sobj_minus_square(struct Sobj* obj1, struct Sobj* obj2) {
    SDL_Rect *rect1 = get_userdata(obj1);
    SDL_Rect *rect2 = get_userdata(obj2);

    SDL_Rect *rect3 = Screat_rect(rect1->x - rect2->x, rect1->y - rect2->y, rect1->w - rect2->w, rect1->h - rect2->h);

    struct Sobj* userdata = Sobj_make_userdata(rect3);
    userdata->meta = obj1->meta;

    return userdata;
}

struct Sobj* Sobj_mul_square(struct Sobj* obj1, struct Sobj* obj2) {
    SDL_Rect *rect1 = get_userdata(obj1);
    SDL_Rect *rect2 = get_userdata(obj2);

    SDL_Rect *rect3 = Screat_rect(rect1->x * rect2->x, rect1->y * rect2->y, rect1->w * rect2->w, rect1->h * rect2->h);

    struct Sobj* userdata = Sobj_make_userdata(rect3);
    userdata->meta = obj1->meta;

    return userdata;
}

struct Sobj* Sobj_div_square(struct Sobj* obj1, struct Sobj* obj2) {
    SDL_Rect *rect1 = get_userdata(obj1);
    SDL_Rect *rect2 = get_userdata(obj2);

    SDL_Rect *rect3 = Screat_rect(rect1->x / rect2->x, rect1->y / rect2->y, rect1->w / rect2->w, rect1->h / rect2->h);

    struct Sobj* userdata = Sobj_make_userdata(rect3);
    userdata->meta = obj1->meta;

    return userdata;
}

struct Sobj* Sobj_equal_square(struct Sobj* obj1, struct Sobj* obj2) {
    SDL_Rect *rect1 = get_userdata(obj1);
    SDL_Rect *rect2 = get_userdata(obj2);

    if (Scollision(rect1, rect2)) {
        return Sobj_make_bool(1);
    } else {
        return Sobj_make_bool(0);
    }
}

struct Sobj* Sobj_make_rect(struct Sframe* frame) {
    struct Sobj* Sx = Sframe_pop(frame);
    struct Sobj* Sy = Sframe_pop(frame);
    struct Sobj* Sw = Sframe_pop(frame);
    struct Sobj* Sh = Sframe_pop(frame);

    int x = Sx->value->value;
    int y = Sy->value->value;
    int w = Sw->value->value;
    int h = Sh->value->value;

    SDL_Rect *rect = Screat_rect(x, y, w, h);

    struct Sobj* userdata = Sobj_make_userdata(rect);

    userdata->meta = Smeta_new();
    userdata->meta->mm_add = Sobj_plus_square;
    userdata->meta->mm_sub = Sobj_minus_square;
    userdata->meta->mm_mul = Sobj_mul_square;
    userdata->meta->mm_div = Sobj_div_square;

    userdata->meta->mm_eq = Sobj_equal_square;

    Sgc_dec_ref(Sx, frame->gc_pool);
    Sgc_dec_ref(Sy, frame->gc_pool);
    Sgc_dec_ref(Sw, frame->gc_pool);
    Sgc_dec_ref(Sh, frame->gc_pool);

    return userdata;
}

struct Sobj* Sinit(struct Sframe* frame) {
    struct Sobj* Stitle = Sframe_pop(frame);
    struct Sobj* Sw = Sframe_pop(frame);
    struct Sobj* Sh = Sframe_pop(frame);

    char* title = Stitle->f_type->f_str->string;
    int w = Sw->value->value;
    int h = Sh->value->value;

    Ginit(title, w, h);

    Sgc_dec_ref(Sw, frame->gc_pool);
    Sgc_dec_ref(Sh, frame->gc_pool);

    return null_obj;
}

struct Sobj* Sscreen_fill(struct Sframe* frame) {
    struct Sobj* Sr = Sframe_pop(frame);
    struct Sobj* Sg = Sframe_pop(frame);
    struct Sobj* Sb = Sframe_pop(frame);

    int r = Sr->value->value;
    int g = Sg->value->value;
    int b = Sb->value->value;

    Gscreen_fill(r, g, b);

    Sgc_dec_ref(Sr, frame->gc_pool);
    Sgc_dec_ref(Sg, frame->gc_pool);
    Sgc_dec_ref(Sb, frame->gc_pool);

    return null_obj;
}

struct Sobj* Sflip(struct Sframe* frame) {
    Gflip();
    return null_obj;
}

struct Sobj* Sclose(struct Sframe* frame) {
    Gclose();
    return null_obj;
}

struct Sobj* Sdraw_square_api(struct Sframe* frame) {
    struct Sobj* Sx = Sframe_pop(frame);
    struct Sobj* Sy = Sframe_pop(frame);
    struct Sobj* Ssize = Sframe_pop(frame);
    struct Sobj* Sr = Sframe_pop(frame);
    struct Sobj* Sg = Sframe_pop(frame);
    struct Sobj* Sb = Sframe_pop(frame);

    float x = (float)Sx->value->value;
    float y = (float)Sy->value->value;
    float size = (float)Ssize->value->value;
    float r = (float)Sr->value->value / 255.0f;
    float g = (float)Sg->value->value / 255.0f;
    float b = (float)Sb->value->value / 255.0f;

    Sdraw_square(x, y, size, r, g, b);

    Sgc_dec_ref(Sx, frame->gc_pool);
    Sgc_dec_ref(Sy, frame->gc_pool);
    Sgc_dec_ref(Ssize, frame->gc_pool);
    Sgc_dec_ref(Sr, frame->gc_pool);
    Sgc_dec_ref(Sg, frame->gc_pool);
    Sgc_dec_ref(Sb, frame->gc_pool);

    return null_obj;
}

struct Sobj* Sdraw_rect_api(struct Sframe* frame) {
    struct Sobj* Sx = Sframe_pop(frame);
    struct Sobj* Sy = Sframe_pop(frame);
    struct Sobj* Sw = Sframe_pop(frame);
    struct Sobj* Sh = Sframe_pop(frame);
    struct Sobj* Sr = Sframe_pop(frame);
    struct Sobj* Sg = Sframe_pop(frame);
    struct Sobj* Sb = Sframe_pop(frame);

    float x = (float)Sx->value->value;
    float y = (float)Sy->value->value;
    float w = (float)Sw->value->value;
    float h = (float)Sh->value->value;
    float r = (float)Sr->value->value / 255.0f;
    float g = (float)Sg->value->value / 255.0f;
    float b = (float)Sb->value->value / 255.0f;

    Sdraw_rect(x, y, w, h, r, g, b);

    Sgc_dec_ref(Sx, frame->gc_pool);
    Sgc_dec_ref(Sy, frame->gc_pool);
    Sgc_dec_ref(Sw, frame->gc_pool);
    Sgc_dec_ref(Sh, frame->gc_pool);
    Sgc_dec_ref(Sr, frame->gc_pool);
    Sgc_dec_ref(Sg, frame->gc_pool);
    Sgc_dec_ref(Sb, frame->gc_pool);

    return null_obj;
}

struct Sobj* Sdraw_line_api(struct Sframe* frame) {
    struct Sobj* Sx1 = Sframe_pop(frame);
    struct Sobj* Sy1 = Sframe_pop(frame);
    struct Sobj* Sx2 = Sframe_pop(frame);
    struct Sobj* Sy2 = Sframe_pop(frame);
    struct Sobj* Sr = Sframe_pop(frame);
    struct Sobj* Sg = Sframe_pop(frame);
    struct Sobj* Sb = Sframe_pop(frame);

    float x1 = (float)Sx1->value->value;
    float y1 = (float)Sy1->value->value;
    float x2 = (float)Sx2->value->value;
    float y2 = (float)Sy2->value->value;
    float r = (float)Sr->value->value / 255.0f;
    float g = (float)Sg->value->value / 255.0f;
    float b = (float)Sb->value->value / 255.0f;

    Sdraw_line(x1, y1, x2, y2, r, g, b);

    Sgc_dec_ref(Sx1, frame->gc_pool);
    Sgc_dec_ref(Sy1, frame->gc_pool);
    Sgc_dec_ref(Sx2, frame->gc_pool);
    Sgc_dec_ref(Sy2, frame->gc_pool);
    Sgc_dec_ref(Sr, frame->gc_pool);
    Sgc_dec_ref(Sg, frame->gc_pool);
    Sgc_dec_ref(Sb, frame->gc_pool);

    return null_obj;
}

struct Sobj* Sget_key_api(struct Sframe* frame) {
    char key = SGL_get_key();
    return Sobj_make_char(key);
}

SUNY_API struct Sframe* Smain(struct Sframe* frame, struct Scompiler* compiler) {
    SunyInitialize_c_api_func(frame, compiler, 51, "init", 3, Sinit);
    SunyInitialize_c_api_func(frame, compiler, 52, "screen_fill", 3, Sscreen_fill);
    SunyInitialize_c_api_func(frame, compiler, 53, "flip", 0, Sflip);
    SunyInitialize_c_api_func(frame, compiler, 54, "close", 0, Sclose);
    SunyInitialize_c_api_func(frame, compiler, 55, "draw_square", 6, Sdraw_square_api);
    SunyInitialize_c_api_func(frame, compiler, 56, "draw_rect", 7, Sdraw_rect_api);
    SunyInitialize_c_api_func(frame, compiler, 57, "draw_line", 7, Sdraw_line_api);
    SunyInitialize_c_api_func(frame, compiler, 58, "get_key", 0, Sget_key_api);

    return frame;
}