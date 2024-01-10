#include "Counter.hpp"
#include <string>

Counter::Counter()
{
    textColor = {255, 255, 255};
}

Counter::~Counter()
{
    SDL_DestroyTexture(texture);
}

ScoreCounter::ScoreCounter(SDL_Renderer *renderer, TTF_Font *font, int x, int y)
{
    mRenderer = renderer;
    mFont = font;
    mScore = 0;

    Rect.x = x;
    Rect.y = y;
    Rect.h = 32;
    Rect.w = 64;
}

void ScoreCounter::update(int points)
{
    mScore += points;
}

void ScoreCounter::render()
{
    text = "Score: " + std::to_string(mScore);
    surface = TTF_RenderText_Solid(mFont, text.c_str(), textColor);

    texture = SDL_CreateTextureFromSurface(mRenderer, surface); // Создание текстуры из поверхности
    SDL_FreeSurface(surface); // Освобождение поверхности

    SDL_QueryTexture(texture, nullptr, nullptr, &Rect.w, &Rect.h);
    SDL_RenderCopy(mRenderer, texture, nullptr, &Rect);
}

TimeCounter::TimeCounter(SDL_Renderer *renderer, TTF_Font *font, int duration, int x, int y)
{
    mRenderer = renderer;
    mFont = font;
    mRemainingTime = duration;
    counting = 0;

    Rect.x = x;
    Rect.y = y;
    Rect.h = 32;
    Rect.w = 64;
}

bool TimeCounter::update()
{
    counting++;
    if (!(counting % 60))
        mRemainingTime--;

    if (!mRemainingTime)
        return false;
    return true;
}

void TimeCounter::render()
{
    text = "Time: " + std::to_string(mRemainingTime);
    surface = TTF_RenderText_Solid(mFont, text.c_str(), textColor);

    texture = SDL_CreateTextureFromSurface(mRenderer, surface);
    SDL_FreeSurface(surface);

    SDL_QueryTexture(texture, nullptr, nullptr, &Rect.w, &Rect.h);
    SDL_RenderCopy(mRenderer, texture, nullptr, &Rect);
}
