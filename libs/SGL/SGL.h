#ifndef SGL_H
#define SGL_H

#include <SDL2/SDL.h>

#include "SGL_keys.h"

#if !defined(GUI)
    #define GUI extern
    #ifdef WIN32
        #define GUI_API __declspec(dllexport)
    #else
        #define GUI_API
    #endif
#endif

struct Cube {
    float x, y, z;
    float r, g, b;

    int address;
};

#define creat_address(c) (++start)

GUI int start;

GUI SDL_Window* window;
GUI SDL_Renderer* renderer;

GUI int user_quit;

GUI struct Cube** cubes;

GUI int num_cubes;
GUI int max_cubes;

GUI_API void Ginit(char* title, int w, int h);
GUI_API void Gscreen_fill(int r, int g, int b);

GUI_API void Gclose();
GUI_API void Gflip();

GUI_API void Sdraw_square(float x, float y, float size, float r, float g, float b);
GUI_API void Sdraw_rect(float x, float y, float w, float h, float r, float g, float b);
GUI_API void Sdraw_line(float x1, float y1, float x2, float y2, float r, float g, float b);

GUI_API SDL_Rect *Screat_rect(float x, float y, float w, float h);

GUI_API int Scollision(SDL_Rect* rect1, SDL_Rect* rect2);

GUI_API Uint8* Sget_keyState();

GUI_API char SGL_get_key();

#endif // SGL_H