#pragma once
#include "Game.hpp"
#include "ScoreObjects.hpp"
#include "Counter.hpp"
#include <vector>
#include <memory>

class ObjectManager
{
private:
    std::vector<std::unique_ptr<ScoreObjects>> objects;

public:
    ~ObjectManager();
    void clearObjects();
    void addLamp(int count, SDL_Renderer *ren);
    void addCandle(int count, SDL_Renderer *ren);
    void addChandelier(int count, SDL_Renderer *ren);
    void addRedMan(int count, SDL_Renderer *ren);
    void addVioletMan(int count, SDL_Renderer *ren);
    void addOrangeMan(int count, SDL_Renderer *ren);

    int update(GameObject *MainObject, ScoreCounter* cntObject);
    void render();
};
