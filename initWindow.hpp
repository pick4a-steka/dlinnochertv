#pragma once
#include "Game.hpp"

class initWindow
{
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *backSurface;
    SDL_Texture *backTexture;
    TTF_Font *gFont;
    SDL_Rect mapRect;
    bool isRunning;
public:
    void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);
    void changeBack(const char *nameBack); // Смена фона
    void isCloseWindow();
    void renderBack();
    void clean();
    SDL_Renderer* GetRenderer()
    {
        return renderer;
    }
    TTF_Font* GetFont()
    {
        return gFont;
    }
    SDL_Texture* GetTexture()
    {
        return backTexture;
    }
    SDL_Rect GetRect()
    {
        return mapRect;
    }
    bool mainRunning()
    {
        return isRunning;
    }
};
