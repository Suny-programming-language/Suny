#include "SGL.h"

int start = 0;
int user_quit = 0;
int num_cubes = 0;
int max_cubes = 0;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

struct Cube** cubes = NULL;

GUI_API void Ginit(char* title, int w, int h) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, 0);

    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);

    if (!renderer) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return;
    }
}

GUI_API void Gscreen_fill(int r, int g, int b) {
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderClear(renderer);
}

GUI_API void Gclose() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    exit(0);
}

GUI_API void Gflip() {
    if (user_quit) {
        Gclose();
        return;
    }

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            user_quit = 1;
            return;
        }
    }

    SDL_RenderPresent(renderer);
}

static inline Uint8 f2c(float v) {
    if (v < 0) v = 0;
    if (v > 1) v = 1;
    return (Uint8)(v * 255);
}

GUI_API void Sdraw_square(float x, float y, float size, float r, float g, float b) {
    SDL_Rect rect = { (int)x, (int)y, (int)size, (int)size };
    SDL_SetRenderDrawColor(renderer, f2c(r), f2c(g), f2c(b), 255);
    SDL_RenderFillRect(renderer, &rect);
}

GUI_API void Sdraw_rect(float x, float y, float w, float h, float r, float g, float b) {
    SDL_Rect rect = { (int)x, (int)y, (int)w, (int)h };
    SDL_SetRenderDrawColor(renderer, f2c(r), f2c(g), f2c(b), 255);
    SDL_RenderFillRect(renderer, &rect);
}

GUI_API void Sdraw_line(float x1, float y1, float x2, float y2, float r, float g, float b) {
    SDL_SetRenderDrawColor(renderer, f2c(r), f2c(g), f2c(b), 255);
    SDL_RenderDrawLine(renderer, (int)x1, (int)y1, (int)x2, (int)y2);
}

GUI_API char SGL_get_key() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            SDL_Keycode key = event.key.keysym.sym;

            if (key >= 'a' && key <= 'z') {
                return 'a' + (key - 'a');
            }
            else if (key >= SDLK_0 && key <= SDLK_9) {
                return '0' + (key - SDLK_0);
            }
            else {
                switch (key) {
                    case SDLK_RETURN:  return '\n';
                    case SDLK_SPACE:   return ' ';
                    case SDLK_ESCAPE:  return 27;
                    default: return 0;
                }
            }
        }
        else if (event.type == SDL_QUIT) {
            user_quit = 1;
            exit(1);
        }
    }

    return 0;
}

GUI_API SDL_Rect *Screat_rect(float x, float y, float w, float h) {
    SDL_Rect* rect = malloc(sizeof(SDL_Rect));
    rect->x = (int)x;
    rect->y = (int)y;
    rect->w = (int)w;
    rect->h = (int)h;
    return rect;
}

GUI_API int Scollision(SDL_Rect* rect1, SDL_Rect* rect2) {
    return SDL_HasIntersection(rect1, rect2);
}