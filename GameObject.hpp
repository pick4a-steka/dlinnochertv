#pragma once
#include "Game.hpp"

class GameObject
{
private:
    int xpos;
    int ypos;

    SDL_Texture *objTexture; // ������ ��� �������� ���c������ ������
    SDL_Rect srcRect, destRect; // ������������� ��������� � ������������� ����������
    SDL_Renderer *renderer;
public:
    GameObject(const char *texturesheet, SDL_Renderer *ren);
    ~GameObject();

    void moveLeft();
    void moveRight(int winW);
    void moveUp();
    void moveDown(int winH);
    void Update();
    void Render();
    int GetXpos()
    {
        return xpos;
    }
    int GetYpos()
    {
        return ypos;
    }
    int GetDestRect_h()
    {
        return destRect.h;
    }
    int GetDestRect_w()
    {
        return destRect.w;
    }
};
