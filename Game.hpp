#ifndef Game_hpp
#define Game_hpp

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

class Game
{
private:
    bool isRunning;
    int score;
public:

    Game();
    ~Game();

    void handleEvents(bool& isPause, bool& isGameOver); // ��������� ������� �������

    void update(bool isPause); // ������� ��� ���������� ������� ��������

    void render(); // ��������� (���������) ����������� �������� �� ������

    void initMobs(SDL_Renderer *renderer, TTF_Font *gFont);

    void reset();

    int GetScore()
    {
        return score;
    }

    bool processGame()
    {
        return isRunning;
    }

    void stop()
    {
        isRunning = false;
    }

};
#endif // Game

