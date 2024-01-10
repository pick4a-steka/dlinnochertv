#include "TextRender.hpp"
#include <string>

TextRender::TextRender(SDL_Renderer* ren, TTF_Font* mFont, SDL_Color mTextColor)
{
    renderer = ren;
    font = mFont;
    textColor = mTextColor;
}

TextRender::~TextRender()
{
    SDL_DestroyTexture(textTexture);
}

void TextRender::setText(const std::string& text)
{
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    SDL_QueryTexture(textTexture, nullptr, nullptr, &textRect.w, &textRect.h);
}

void TextRender::setPosition(int x, int y)
{
    textRect.x = x;
    textRect.y = y;
}

void TextRender::render()
{
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
    // SDL_RenderPresent(renderer);
}
