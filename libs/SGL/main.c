#include "C:/Suny/Suny.h"
#include "SGL.h"

struct Sobj* Sobj_plus_square(struct Sobj* obj1, struct Sobj* obj2) {
    if (obj1->type == USER_DATA_OBJ && obj2->type == USER_DATA_OBJ) {
        SDL_Rect *rect1 = get_userdata(obj1);
        SDL_Rect *rect2 = get_userdata(obj2);

        SDL_Rect *rect3 = Screat_rect(rect1->x + rect2->x, rect1->y + rect2->y, rect1->w + rect2->w, rect1->h + rect2->h);

        struct Sobj* userdata = Sobj_make_userdata(rect3);
        userdata->meta = obj1->meta;

        return userdata;
    } else if (obj1->type == USER_DATA_OBJ && obj2->type == LIST_OBJ) {
        SDL_Rect *rect1 = get_userdata(obj1);

        struct Slist* list = (struct Slist*) Sobj_get_obj(obj2, LIST_OBJ);
        if (list->count != 2) {
            printf("The size of list must be 2\n");
            return obj1;
        }

        struct Sobj* obj2_1 = list->array[0];
        struct Sobj* obj2_2 = list->array[1];

        float x = obj2_1->value->value;
        float y = obj2_2->value->value;

        SDL_Rect *rect3 = Screat_rect(rect1->x + x, rect1->y + y, rect1->w, rect1->h);

        struct Sobj* userdata = Sobj_make_userdata(rect3);
        userdata->meta = obj1->meta;

        return userdata;
    } else if (obj1->type == LIST_OBJ && obj2->type == USER_DATA_OBJ) {
        SDL_Rect *rect2 = get_userdata(obj2);

        struct Slist* list = (struct Slist*) Sobj_get_obj(obj1, LIST_OBJ);
        if (list->count != 2) {
            printf("The size of list must be 2\n");
            return obj2;
        }

        struct Sobj* obj1_1 = list->array[0];
        struct Sobj* obj1_2 = list->array[1];

        float x = obj1_1->value->value;
        float y = obj1_2->value->value;

        SDL_Rect *rect3 = Screat_rect(x + rect2->x, y + rect2->y, rect2->w, rect2->h);

        struct Sobj* userdata = Sobj_make_userdata(rect3);
        userdata->meta = obj2->meta;

        return userdata;
    } 

    return obj1;
}

struct Sobj* Sobj_minus_square(struct Sobj* obj1, struct Sobj* obj2) {
    if (obj1->type == USER_DATA_OBJ && obj2->type == USER_DATA_OBJ) {
        SDL_Rect *rect1 = get_userdata(obj1);
        SDL_Rect *rect2 = get_userdata(obj2);

        SDL_Rect *rect3 = Screat_rect(rect1->x - rect2->x, rect1->y - rect2->y, rect1->w - rect2->w, rect1->h - rect2->h);

        struct Sobj* userdata = Sobj_make_userdata(rect3);
        userdata->meta = obj1->meta;

        return userdata;
    } else if (obj1->type == USER_DATA_OBJ && obj2->type == LIST_OBJ) {
        SDL_Rect *rect1 = get_userdata(obj1);

        struct Slist* list = (struct Slist*) Sobj_get_obj(obj2, LIST_OBJ);
        if (list->count != 2) {
            printf("The size of list must be 2\n");
            return obj1;
        }

        struct Sobj* obj2_1 = list->array[0];
        struct Sobj* obj2_2 = list->array[1];

        float x = obj2_1->value->value;
        float y = obj2_2->value->value;

        SDL_Rect *rect3 = Screat_rect(rect1->x - x, rect1->y - y, rect1->w, rect1->h);

        struct Sobj* userdata = Sobj_make_userdata(rect3);
        userdata->meta = obj1->meta;

        return userdata;
    } else if (obj1->type == LIST_OBJ && obj2->type == USER_DATA_OBJ) {
        SDL_Rect *rect2 = get_userdata(obj2);

        struct Slist* list = (struct Slist*) Sobj_get_obj(obj1, LIST_OBJ);
        if (list->count != 2) {
            printf("The size of list must be 2\n");
            return obj2;
        }

        struct Sobj* obj1_1 = list->array[0];
        struct Sobj* obj1_2 = list->array[1];

        float x = obj1_1->value->value;
        float y = obj1_2->value->value;

        SDL_Rect *rect3 = Screat_rect(x - rect2->x, y - rect2->y, rect2->w, rect2->h);

        struct Sobj* userdata = Sobj_make_userdata(rect3);
        userdata->meta = obj2->meta;

        return userdata;
    }

    return obj1;
}

struct Sobj* Sobj_mul_square(struct Sobj* obj1, struct Sobj* obj2) {
    if (obj1->type == USER_DATA_OBJ && obj2->type == USER_DATA_OBJ) {
        SDL_Rect *rect1 = get_userdata(obj1);
        SDL_Rect *rect2 = get_userdata(obj2);

        SDL_Rect *rect3 = Screat_rect(rect1->x * rect2->x, rect1->y * rect2->y, rect1->w * rect2->w, rect1->h * rect2->h);

        struct Sobj* userdata = Sobj_make_userdata(rect3);
        userdata->meta = obj1->meta;

        return userdata;
    } else if (obj1->type == USER_DATA_OBJ && obj2->type == LIST_OBJ) {
        SDL_Rect *rect1 = get_userdata(obj1);

        struct Slist* list = (struct Slist*) Sobj_get_obj(obj2, LIST_OBJ);
        if (list->count != 2) {
            printf("The size of list must be 2\n");
            return obj1;
        }

        struct Sobj* obj2_1 = list->array[0];
        struct Sobj* obj2_2 = list->array[1];

        float x = obj2_1->value->value;
        float y = obj2_2->value->value;

        SDL_Rect *rect3 = Screat_rect(rect1->x * x, rect1->y * y, rect1->w, rect1->h);

        struct Sobj* userdata = Sobj_make_userdata(rect3);
        userdata->meta = obj1->meta;

        return userdata;
    } else if (obj1->type == LIST_OBJ && obj2->type == USER_DATA_OBJ) {
        SDL_Rect *rect2 = get_userdata(obj2);

        struct Slist* list = (struct Slist*) Sobj_get_obj(obj1, LIST_OBJ);
        if (list->count != 2) {
            printf("The size of list must be 2\n");
            return obj2;
        }

        struct Sobj* obj1_1 = list->array[0];
        struct Sobj* obj1_2 = list->array[1];

        float x = obj1_1->value->value;
        float y = obj1_2->value->value;

        SDL_Rect *rect3 = Screat_rect(x * rect2->x, y * rect2->y, rect2->w, rect2->h);

        struct Sobj* userdata = Sobj_make_userdata(rect3);
        userdata->meta = obj2->meta;

        return userdata;
    }

    return obj1;
}

struct Sobj* Sobj_div_square(struct Sobj* obj1, struct Sobj* obj2) {
    if (obj1->type == USER_DATA_OBJ && obj2->type == USER_DATA_OBJ) {
        SDL_Rect *rect1 = get_userdata(obj1);
        SDL_Rect *rect2 = get_userdata(obj2);

        SDL_Rect *rect3 = Screat_rect(rect1->x / rect2->x, rect1->y / rect2->y, rect1->w / rect2->w, rect1->h / rect2->h);

        struct Sobj* userdata = Sobj_make_userdata(rect3);
        userdata->meta = obj1->meta;

        return userdata;
    } else if (obj1->type == USER_DATA_OBJ && obj2->type == LIST_OBJ) {
        SDL_Rect *rect1 = get_userdata(obj1);

        struct Slist* list = (struct Slist*) Sobj_get_obj(obj2, LIST_OBJ);
        if (list->count != 2) {
            printf("The size of list must be 2\n");
            return obj1;
        }

        struct Sobj* obj2_1 = list->array[0];
        struct Sobj* obj2_2 = list->array[1];

        float x = obj2_1->value->value;
        float y = obj2_2->value->value;

        SDL_Rect *rect3 = Screat_rect(rect1->x / x, rect1->y / y, rect1->w, rect1->h);

        struct Sobj* userdata = Sobj_make_userdata(rect3);
        userdata->meta = obj1->meta;

        return userdata;
    } else if (obj1->type == LIST_OBJ && obj2->type == USER_DATA_OBJ) {
        SDL_Rect *rect2 = get_userdata(obj2);

        struct Slist* list = (struct Slist*) Sobj_get_obj(obj1, LIST_OBJ);
        if (list->count != 2) {
            printf("The size of list must be 2\n");
            return obj2;
        }

        struct Sobj* obj1_1 = list->array[0];
        struct Sobj* obj1_2 = list->array[1];

        float x = obj1_1->value->value;
        float y = obj1_2->value->value;    

        SDL_Rect *rect3 = Screat_rect(x / rect2->x, y / rect2->y, rect2->w, rect2->h);

        struct Sobj* userdata = Sobj_make_userdata(rect3);
        userdata->meta = obj2->meta;

        return userdata;
    }

    return obj1;
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

struct Sobj* Sio_print_rect(struct Sobj* obj) {
    SDL_Rect *rect = get_userdata(obj);
    printf("rect: x: %d, y: %d, w: %d, h: %d", rect->x, rect->y, rect->w, rect->h);
    return null_obj;
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

    userdata->meta->mm_tostring = Sio_print_rect;

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

struct Sobj* Sdraw_rect_api_with_SGL_rect(struct Sframe* frame) {
    struct Sobj* Srect = Sframe_pop(frame);
    struct Sobj* Sr = Sframe_pop(frame);
    struct Sobj* Sg = Sframe_pop(frame);
    struct Sobj* Sb = Sframe_pop(frame);

    SDL_Rect *rect = get_userdata(Srect);
    float r = (float)Sr->value->value / 255.0f;
    float g = (float)Sg->value->value / 255.0f;
    float b = (float)Sb->value->value / 255.0f;

    Sdraw_rect(rect->x, rect->y, rect->w, rect->h, r, g, b);

    Sgc_dec_ref(Srect, frame->gc_pool);

    Sgc_dec_ref(Sr, frame->gc_pool);
    Sgc_dec_ref(Sg, frame->gc_pool);
    Sgc_dec_ref(Sb, frame->gc_pool);

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

struct Slist* Slist_creat_multi_value(int size, struct Sobj* value) {
    struct Slist* list = Slist_new();

    for (int i = 0; i < size; i++) {
        struct Sobj* deep_copy = Sobj_deep_copy(value);
        inc_ref(deep_copy);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
        Slist_add(list, deep_copy);
    }

    return list;
}

struct Sobj* Sobj_get_key_states(struct Sframe* frame) {
    struct Sobj* fobj = Sobj_make_false();
    struct Slist* list = Slist_creat_multi_value(MAX_KEYS_LAPTOP, fobj);
    
    int numKeys;
    const Uint8* state = SDL_GetKeyboardState(&numKeys);

    int sdl_to_sgl[MAX_KEYS_LAPTOP] = {0};

    sdl_to_sgl[SDL_SCANCODE_F1] = KEY_F1;
    sdl_to_sgl[SDL_SCANCODE_F2] = KEY_F2;
    sdl_to_sgl[SDL_SCANCODE_F3] = KEY_F3;
    sdl_to_sgl[SDL_SCANCODE_F4] = KEY_F4;
    sdl_to_sgl[SDL_SCANCODE_F5] = KEY_F5;
    sdl_to_sgl[SDL_SCANCODE_F6] = KEY_F6;
    sdl_to_sgl[SDL_SCANCODE_F7] = KEY_F7;
    sdl_to_sgl[SDL_SCANCODE_F8] = KEY_F8;
    sdl_to_sgl[SDL_SCANCODE_F9] = KEY_F9;
    sdl_to_sgl[SDL_SCANCODE_F10] = KEY_F10;
    sdl_to_sgl[SDL_SCANCODE_F11] = KEY_F11;
    sdl_to_sgl[SDL_SCANCODE_F12] = KEY_F12;

    sdl_to_sgl[SDL_SCANCODE_Q] = KEY_Q;
    sdl_to_sgl[SDL_SCANCODE_W] = KEY_W;
    sdl_to_sgl[SDL_SCANCODE_E] = KEY_E;
    sdl_to_sgl[SDL_SCANCODE_R] = KEY_R;
    sdl_to_sgl[SDL_SCANCODE_T] = KEY_T;
    sdl_to_sgl[SDL_SCANCODE_Y] = KEY_Y;
    sdl_to_sgl[SDL_SCANCODE_U] = KEY_U;
    sdl_to_sgl[SDL_SCANCODE_I] = KEY_I;
    sdl_to_sgl[SDL_SCANCODE_O] = KEY_O;
    sdl_to_sgl[SDL_SCANCODE_P] = KEY_P;

    sdl_to_sgl[SDL_SCANCODE_A] = KEY_A;
    sdl_to_sgl[SDL_SCANCODE_S] = KEY_S;
    sdl_to_sgl[SDL_SCANCODE_D] = KEY_D;
    sdl_to_sgl[SDL_SCANCODE_F] = KEY_F;
    sdl_to_sgl[SDL_SCANCODE_G] = KEY_G;
    sdl_to_sgl[SDL_SCANCODE_H] = KEY_H;
    sdl_to_sgl[SDL_SCANCODE_J] = KEY_J;
    sdl_to_sgl[SDL_SCANCODE_K] = KEY_K;
    sdl_to_sgl[SDL_SCANCODE_L] = KEY_L;

    sdl_to_sgl[SDL_SCANCODE_Z] = KEY_Z;
    sdl_to_sgl[SDL_SCANCODE_X] = KEY_X;
    sdl_to_sgl[SDL_SCANCODE_C] = KEY_C;
    sdl_to_sgl[SDL_SCANCODE_V] = KEY_V;
    sdl_to_sgl[SDL_SCANCODE_B] = KEY_B;
    sdl_to_sgl[SDL_SCANCODE_N] = KEY_N;
    sdl_to_sgl[SDL_SCANCODE_M] = KEY_M;

    sdl_to_sgl[SDL_SCANCODE_ESCAPE] = KEY_ESC;
    sdl_to_sgl[SDL_SCANCODE_SPACE] = KEY_SPACE;
    sdl_to_sgl[SDL_SCANCODE_TAB] = KEY_TAB;
    sdl_to_sgl[SDL_SCANCODE_RETURN] = KEY_ENTER;
    sdl_to_sgl[SDL_SCANCODE_BACKSPACE] = KEY_BACKSPACE;

    sdl_to_sgl[SDL_SCANCODE_UP] = KEY_UP;
    sdl_to_sgl[SDL_SCANCODE_DOWN] = KEY_DOWN;
    sdl_to_sgl[SDL_SCANCODE_LEFT] = KEY_LEFT;
    sdl_to_sgl[SDL_SCANCODE_RIGHT] = KEY_RIGHT;

    sdl_to_sgl[SDL_SCANCODE_0] = KEY_0;
    sdl_to_sgl[SDL_SCANCODE_1] = KEY_1;
    sdl_to_sgl[SDL_SCANCODE_2] = KEY_2;
    sdl_to_sgl[SDL_SCANCODE_3] = KEY_3;
    sdl_to_sgl[SDL_SCANCODE_4] = KEY_4;
    sdl_to_sgl[SDL_SCANCODE_5] = KEY_5;
    sdl_to_sgl[SDL_SCANCODE_6] = KEY_6;
    sdl_to_sgl[SDL_SCANCODE_7] = KEY_7;
    sdl_to_sgl[SDL_SCANCODE_8] = KEY_8;
    sdl_to_sgl[SDL_SCANCODE_9] = KEY_9;

    for (int i = 0; i < numKeys; i++) {
        if (state[i] && sdl_to_sgl[i] >= 0 && sdl_to_sgl[i] < MAX_KEYS_LAPTOP) {
            struct Sobj* boolen = Sobj_make_true();
            inc_ref(boolen);
            Slist_change_item(list, sdl_to_sgl[i], boolen);
        }
    }

    struct Sobj* ret = Sobj_make_list(list);
    return ret;
}

SUNY_API struct Sframe* Smain(struct Sframe* frame, struct Scompiler* compiler) {
    SunyInitialize_c_api_func(frame, compiler, 51, "SGL_init", 3, Sinit);
    SunyInitialize_c_api_func(frame, compiler, 52, "SGL_screen_fill", 3, Sscreen_fill);
    SunyInitialize_c_api_func(frame, compiler, 53, "SGL_flip", 0, Sflip);
    SunyInitialize_c_api_func(frame, compiler, 54, "SGL_close", 0, Sclose);
    SunyInitialize_c_api_func(frame, compiler, 55, "SGL_draw_square", 6, Sdraw_square_api);
    SunyInitialize_c_api_func(frame, compiler, 56, "SGL_draw_rect", 7, Sdraw_rect_api);
    SunyInitialize_c_api_func(frame, compiler, 57, "SGL_draw_line", 7, Sdraw_line_api);
    SunyInitialize_c_api_func(frame, compiler, 58, "SGL_get_key", 0, Sget_key_api);

    SunyInitialize_c_api_func(frame, compiler, 59, "SGL_rect", 0, Sobj_make_rect);
    SunyInitialize_c_api_func(frame, compiler, 60, "SGL_draw_rect", 0, Sdraw_rect_api_with_SGL_rect);

    SunyInitialize_c_api_func(frame, compiler, 61, "SGL_get_key_states", 0, Sobj_get_key_states);

    return frame;
}