#include "TextureManager.hpp"

SDL_Texture* TextureManager::LoadTexture(const char *texture, SDL_Renderer *ren)
{
    SDL_Surface *tmpSurface = IMG_Load(texture); // SDL_Surface - это структура данных, которая представляет изображение в памяти в виде массива пикселей
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, tmpSurface); // Создаём новый объект SDL_Texture на основе существующего SDL_Surface
    SDL_FreeSurface(tmpSurface); // Освобождаем память занимаемую объектом SDL_Surface (Освобождаем существующую поверхность)

    return tex;
}
