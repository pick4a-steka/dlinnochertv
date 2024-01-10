#include "ScoreObjects.hpp"
#include "TextureManager.hpp"
#include "Game.hpp"
#include "ConstantsSize.h"
#include <cstdlib>

ScoreObjects::ScoreObjects()
{
    windowHeight = HEIGHT;
    windowWidth = WIDTH;
}

ScoreObjects::~ScoreObjects()
{

}

void ScoreObjects::initializeTexture(const char *TextureName, SDL_Renderer *ren)
{
    ren_entity = ren;
    Tex_entity = TextureManager::LoadTexture(TextureName, ren);
}

bool ScoreObjects::interactionManager(int x, int y, int drX, int drY, GameObject* gObj)
{
    if (((x > gObj->GetXpos() || x + drX > gObj->GetXpos()) && (x < gObj->GetXpos() + gObj->GetDestRect_w() || x + drX < gObj->GetXpos() + gObj->GetDestRect_w())) &&
        ((y > gObj->GetYpos() || y + drY > gObj->GetYpos()) && (y < gObj->GetYpos() + gObj->GetDestRect_h() || y + drY < gObj->GetYpos() + gObj->GetDestRect_h())))
    {
        return true;
    }

    return false;
}

Candle::Candle(const char *TextureName, SDL_Renderer *ren) : ScoreObjects()
{
    initializeTexture(TextureName, ren);

    srcRect.h = 32;
    srcRect.w = 32;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.h = srcRect.h;
    destRect.w = srcRect.w;

    scoreValue = 10;
}

void Candle::Update()
{
    destRect.x = xpos;
    destRect.y = ypos;
}

void Candle::Render()
{
    SDL_RenderCopy(ren_entity, Tex_entity, &srcRect, &destRect);
}

void Candle::randomPosition()
{
    xpos = rand() % (windowWidth - destRect.w + 1);
    ypos = rand() % (windowHeight - destRect.h + 1);
}

bool Candle::interaction(GameObject* gObj)
{
    return interactionManager(xpos, ypos, destRect.w, destRect.h, gObj);
}

Lamp::Lamp(const char *TextureName, SDL_Renderer *ren) : ScoreObjects()
{
    initializeTexture(TextureName, ren);

    srcRect.h = 32;
    srcRect.w = 32;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.h = srcRect.h;
    destRect.w = srcRect.w;

    scoreValue = 5;
}

void Lamp::Update()
{
    destRect.x = xpos;
    destRect.y = ypos;
}

void Lamp::Render()
{
    SDL_RenderCopy(ren_entity, Tex_entity, &srcRect, &destRect);
}

void Lamp::randomPosition()
{
    xpos = rand() % (windowWidth - destRect.w + 1);
    ypos = rand() % (windowHeight - destRect.h + 1);
}

bool Lamp::interaction(GameObject *gObj)
{
    return interactionManager(xpos, ypos, destRect.w, destRect.h, gObj);
}

Chandelier::Chandelier(const char *TextureName, SDL_Renderer *ren) : ScoreObjects()
{
    initializeTexture(TextureName, ren);

    srcRect.h = 32;
    srcRect.w = 32;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.h = srcRect.h;
    destRect.w = srcRect.w;

    scoreValue = 15;
}

void Chandelier::Update()
{
    destRect.x = xpos;
    destRect.y = ypos;
}

void Chandelier::Render()
{
    SDL_RenderCopy(ren_entity, Tex_entity, &srcRect, &destRect);
}

void Chandelier::randomPosition()
{
    xpos = rand() % (windowWidth - destRect.w + 1);
    ypos = rand() % (windowHeight - destRect.h + 1);
}

bool Chandelier::interaction(GameObject *gObj)
{
    return interactionManager(xpos, ypos, destRect.w, destRect.h, gObj);
}

Red_man::Red_man(const char *TextureName, SDL_Renderer *ren) : ScoreObjects()
{
    initializeTexture(TextureName, ren);

    srcRect.h = 48;
    srcRect.w = 48;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.h = srcRect.h;
    destRect.w = srcRect.w;

    scoreValue = -5;
}

void Red_man::Update()
{
    destRect.x = xpos;
    destRect.y = ypos;
}

void Red_man::Render()
{
    SDL_RenderCopy(ren_entity, Tex_entity, &srcRect, &destRect);
}

void Red_man::randomPosition()
{
    xpos = rand() % (windowWidth - destRect.w + 1);
    ypos = rand() % (windowHeight - destRect.h + 1);
}

bool Red_man::interaction(GameObject *gObj)
{
    return interactionManager(xpos, ypos, destRect.w, destRect.h, gObj);
}

Violet_man::Violet_man(const char *TextureName, SDL_Renderer *ren) : ScoreObjects()
{
    initializeTexture(TextureName, ren);

    srcRect.h = 48;
    srcRect.w = 48;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.h = srcRect.h;
    destRect.w = srcRect.w;

    scoreValue = -5;
}

void Violet_man::Update()
{
    destRect.x = xpos;
    destRect.y = ypos;
}

void Violet_man::Render()
{
    SDL_RenderCopy(ren_entity, Tex_entity, &srcRect, &destRect);
}

void Violet_man::randomPosition()
{
    xpos = rand() % (windowWidth - destRect.w + 1);
    ypos = rand() % (windowHeight - destRect.h + 1);
}

bool Violet_man::interaction(GameObject *gObj)
{
    return interactionManager(xpos, ypos, destRect.w, destRect.h, gObj);
}

Orange_man::Orange_man(const char *TextureName, SDL_Renderer *ren) : ScoreObjects()
{
    initializeTexture(TextureName, ren);

    srcRect.h = 48;
    srcRect.w = 48;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.h = srcRect.h;
    destRect.w = srcRect.w;

    scoreValue = -5;
}

void Orange_man::Update()
{
    destRect.x = xpos;
    destRect.y = ypos;
}

void Orange_man::Render()
{
    SDL_RenderCopy(ren_entity, Tex_entity, &srcRect, &destRect);
}

void Orange_man::randomPosition()
{
    xpos = rand() % (windowWidth - destRect.w + 1);
    ypos = rand() % (windowHeight - destRect.h + 1);
}

bool Orange_man::interaction(GameObject *gObj)
{
    return interactionManager(xpos, ypos, destRect.w, destRect.h, gObj);
}
