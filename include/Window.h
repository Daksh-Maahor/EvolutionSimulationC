#ifndef WINDOW_H_
#define WINDOW_H_

#include <SDL2/SDL.h>

typedef struct
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    int width, height;
} Window;

Window* CreateWindow(const char* title, int width, int height);
int GetRefreshRate(Window* window);
void DestroyWindow(Window* window);
void ClearScreen(Window* window);
void Display(Window* window);
void FillRect(Window* window, int x, int y, int w, int h, uint8_t r, uint8_t g, uint8_t b);
void DrawLine(Window* window, float x1, float y1, float x2, float y2, uint8_t r, uint8_t g, uint8_t b);

#endif
