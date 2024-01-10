#include "initWindow.hpp"
#include "ConstantsSize.h"

void initWindow::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flag = 0;
    if (fullscreen) // Условие для создания полноэкранного режима
    {
        flag = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) // Проверка на правильность инициализации
    {
        std::cout << "Subsystem Initialised!..." << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flag); // Передаем параметры окну
        if (window)
        {
            std::cout << "Window created!" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer created!" << std::endl;
        }

        isRunning = true; // Игра запущена
    }
    else
    {
        isRunning = false; // Игра НЕ запущена
    }

    TTF_Init();
    gFont = TTF_OpenFont("fonts/Samson.ttf", 24);
}

void initWindow::changeBack(const char *nameBack)
{
    backSurface = IMG_Load(nameBack);
    if (backSurface)
    {
        backTexture = SDL_CreateTextureFromSurface(renderer, backSurface);
        SDL_FreeSurface(backSurface);
        mapRect.x = 0;
        mapRect.y = 0;
        mapRect.h = HEIGHT;
        mapRect.w = WIDTH;
        std::cout << "Map created!" << std::endl;
    }
}

void initWindow::isCloseWindow()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT)
    {
        isRunning = false;
    }
}

void initWindow::renderBack()
{
    SDL_RenderCopy(renderer, backTexture, nullptr, &mapRect);
}

void initWindow::clean()
{
    TTF_CloseFont(gFont);
    TTF_Quit();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    std::cout << "Game Cleaned" << std::endl;
}
