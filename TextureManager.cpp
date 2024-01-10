#include "TextureManager.hpp"

SDL_Texture* TextureManager::LoadTexture(const char *texture, SDL_Renderer *ren)
{
    SDL_Surface *tmpSurface = IMG_Load(texture); // SDL_Surface - ��� ��������� ������, ������� ������������ ����������� � ������ � ���� ������� ��������
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, tmpSurface); // ������ ����� ������ SDL_Texture �� ������ ������������� SDL_Surface
    SDL_FreeSurface(tmpSurface); // ����������� ������ ���������� �������� SDL_Surface (����������� ������������ �����������)

    return tex;
}
