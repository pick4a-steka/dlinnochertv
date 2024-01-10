#include "Game.hpp"
#include "ConstantsSize.h"
#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "ScoreObjects.hpp"
#include "ObjectManager.hpp"
#include "Counter.hpp"

GameObject *dlinnochertv;
ObjectManager manager;
ScoreCounter *scoreCounter;
TimeCounter *timeCounter;

Game::Game()
{
    isRunning = true;
}

Game::~Game()
{
    delete scoreCounter;
    delete timeCounter;
}

void Game::initMobs(SDL_Renderer *renderer, TTF_Font *gFont)
{
    scoreCounter = new ScoreCounter(renderer, gFont, 540, 0);
    timeCounter = new TimeCounter(renderer, gFont, 30, 0, 0);

    dlinnochertv = new GameObject("active/dlinnochertv1.png", renderer);
    manager.addCandle(2, renderer);
    manager.addChandelier(1, renderer);
    manager.addLamp(3, renderer);
    manager.addRedMan(2, renderer);
    manager.addOrangeMan(2, renderer);
    manager.addVioletMan(2, renderer);
}

void Game::handleEvents(bool& isPause, bool& isGameOver)
{
    SDL_Event event;
    SDL_PollEvent(&event); // ‘ункци€, котора€ провер€ет очередь на событи€. ќна извлекает первое событие из очереди и если оно существует, возвращает 1, иначе 0
    switch (event.type)
    {
        case SDL_QUIT :
        {
            isRunning = false;
            break;
        }
        case SDL_KEYDOWN :
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_LEFT :
                {
                    if(!isPause) dlinnochertv->moveLeft();
                    break;
                }
                case SDLK_RIGHT :
                {
                    if(!isPause) dlinnochertv->moveRight(WIDTH);
                    break;
                }
                case SDLK_UP :
                {
                    if(!isPause) dlinnochertv->moveUp();
                    break;
                }
                case SDLK_DOWN :
                {
                    if(!isPause) dlinnochertv->moveDown(HEIGHT);
                    break;
                }
                case SDLK_ESCAPE :
                {
                    isPause = !isPause;
                    break;
                }
                case SDLK_BACKSPACE :
                {
                    if (isPause)
                    {
                        stop();
                        isGameOver = false;
                    }
                    break;
                }
                default : break;
            }
            break;
        }
        default : break;
    }
}

void Game::update(bool isPause)
{
    dlinnochertv->Update();
    score = manager.update(dlinnochertv, scoreCounter);
    if (!isPause)
    {
        isRunning = timeCounter->update();
    }
}

void Game::render()
{
    dlinnochertv->Render();
    manager.render();
    scoreCounter->render();
    timeCounter->render();
}

void Game::reset()
{
    isRunning = true;
    manager.clearObjects();
}
