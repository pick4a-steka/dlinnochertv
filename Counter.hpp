#pragma once
#include "Game.hpp"
#include <string>

class Counter
{
protected:
    SDL_Color textColor;
    SDL_Renderer *mRenderer;
    TTF_Font *mFont;
    std::string text;
    SDL_Surface *surface;
    SDL_Rect Rect;
    SDL_Texture *texture;
public:
    Counter();
    virtual ~Counter();
    virtual void render() = 0;
};

class ScoreCounter : public Counter
{
private:
    int mScore;
public:
    ScoreCounter(SDL_Renderer *renderer, TTF_Font* font, int x, int y);
    void update(int points);
    void render() override;
    int GetScore()
    {
        return mScore;
    }
};

class TimeCounter : public Counter
{
private:
    int mRemainingTime;
    int counting;
public:
    TimeCounter(SDL_Renderer *renderer, TTF_Font *font, int duration, int x, int y);
    bool update();
    void render() override;
};
