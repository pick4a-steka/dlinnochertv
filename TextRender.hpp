#pragma once
#include "Game.hpp"

class TextRender
{
private:
    SDL_Renderer *renderer;
    TTF_Font *font;
    SDL_Color textColor;
    SDL_Texture *textTexture;
    SDL_Rect textRect;
public:
    TextRender(SDL_Renderer* ren, TTF_Font* mFont, SDL_Color mTextColor);
    ~TextRender();
    void setText(const std::string& text);
    void setPosition(int x, int y);
    void render();
};
