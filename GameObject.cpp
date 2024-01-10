#include "GameObject.hpp"
#include "TextureManager.hpp"

GameObject::GameObject(const char *texturesheet, SDL_Renderer *ren)
{
    renderer = ren;
    objTexture = TextureManager::LoadTexture(texturesheet, ren);
    xpos = 18; ypos = 7;
}

void GameObject::Update()
{

    srcRect.h = 64;
    srcRect.w = 32;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.h = srcRect.h;
    destRect.w = srcRect.w;
    destRect.x = xpos;
    destRect.y = ypos;
}

void GameObject::Render()
{
    SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect); //  опируем часть текстуры в определЄнную позицию на текущие цели рендеринга
}

void GameObject::moveLeft()
{
    xpos -= 5;
    if (xpos < 0)
        xpos = 0;
}

void GameObject::moveRight(int winW)
{
    xpos += 5;
    if (xpos > winW - destRect.w)
        xpos = winW - destRect.w;
}

void GameObject::moveUp()
{
    ypos -= 5;
    if (ypos < 0)
        ypos = 0;
}

void GameObject::moveDown(int winH)
{
    ypos += 5;
    if (ypos > winH - destRect.h)
        ypos = winH - destRect.h;
}
