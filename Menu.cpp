#include "Menu.hpp"
#include "ConstantsSize.h"
#include "TextRender.hpp"
#include "initWindow.hpp"
#include <string>
#include <fstream>
#include <algorithm>

Menu::Menu(SDL_Renderer *mRenderer, TTF_Font *mFont)
{
    renderer = mRenderer;
    font = mFont;
    selectOptions = 0;
    ProcessReset();
    menuRunning = true;
}

Menu::~Menu()
{
    cleanMenu();
}

void Menu::ProcessReset() // Возвращение всех процессов к их изначальному состоянию
{
    IsChangePlayer = false;
    helpDemonstration = false;
    isRecords = false;
    IsStartGame = false;
}

void Menu::createMenu()
{
    optionsTextures.push_back(createTextTexture("Run the Game"));
    optionsTextures.push_back(createTextTexture("Guide"));
    optionsTextures.push_back(createTextTexture("Player change"));
    optionsTextures.push_back(createTextTexture("Records"));
    optionsTextures.push_back(createTextTexture("Exit"));
}

void Menu::cleanMenu()
{
    for (auto texture : optionsTextures)
    {
        SDL_DestroyTexture(texture);
    }
    optionsTextures.clear();
}

SDL_Texture* Menu::createTextTexture(const std::string &text)
{
    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), {255, 255, 255});
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    return texture;
}

void Menu::handleKeyDown(SDL_Keycode key)
{
    switch (key)
    {
        case SDLK_UP:
            selectOptions = (selectOptions - 1 + optionsTextures.size()) % optionsTextures.size();
            break;
        case SDLK_DOWN:
            selectOptions = (selectOptions + 1) % optionsTextures.size();
            break;
        case SDLK_RETURN:
            handleOptionsSelected(selectOptions);
            break;
    }
}

void Menu::handleMouseClick(int x, int y)
{
    int ypos = HEIGHT / 3;
    int textureWidth, textureHeight;
    for (std::size_t i = 0; i < static_cast<int>(optionsTextures.size()); i++)
    {
        SDL_Texture *texture = optionsTextures[i];
        SDL_QueryTexture(texture, nullptr, nullptr, &textureWidth, &textureHeight);

        if (x >= WIDTH / 5 && x <= WIDTH / 5 + textureWidth && y >= ypos && y <= ypos + textureHeight)
        {
            handleOptionsSelected(i);
            break;
        }
        ypos += 30;
    }
}

void Menu::handleMouseMotion(int x, int y)
{
    int ypos = HEIGHT / 3;
    int textureWidth, textureHeight;
    for (std::size_t i = 0; i < static_cast<int>(optionsTextures.size()); i++)
    {
        SDL_Texture *texture = optionsTextures[i];
        SDL_QueryTexture(texture, nullptr, nullptr, &textureWidth, &textureHeight);

        if (x >= WIDTH / 5 && x <= WIDTH / 5 + textureWidth && y >= ypos && y <= ypos + textureHeight)
        {
            selectOptions = i;
            break;
        }
        ypos += 30;
    }
}

void Menu::handleOptionsSelected(int option)
{
    switch (option)
    {
        case 0:
        {
            // ЗАПУСК ИГРЫ
            IsStartGame = true;
            break;
        }
        case 1:
        {
            // СПРАВКА
            helpDemonstration = true;
            break;
        }
        case 2:
        {
            // СМЕНА ИГРОКА
            IsChangePlayer = true;
            break;
        }
        case 3:
        {
            // РЕКОРДЫ
            isRecords = true;
            std::cout << "Here should be records" << std::endl;
            break;
        }
        case 4:
        {
            // ВЫХОД
            std::cout << "Game over" << std::endl;
            quitGame();
        }
    }
    menuRunning = false;
}

void Menu::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_KEYDOWN:
                handleKeyDown(event.key.keysym.sym);
                break;
            case SDL_MOUSEBUTTONDOWN:
                handleMouseClick(event.button.x, event.button.y);
                break;
            case SDL_MOUSEMOTION:
                handleMouseMotion(event.button.x, event.button.y);
                break;
            case SDL_QUIT:
                quitGame();
                break;
        }
    }
}

void Menu::render()
{
    int ypos = HEIGHT / 3;
    SDL_Texture *texture;
    SDL_Rect destRect;

    for (int i = 0; i < static_cast<int>(optionsTextures.size()); i++)
    {
        texture = optionsTextures[i];
        destRect = {WIDTH / 5, ypos, 0, 0};

        // Выделение выбранного пункта меню
        if (i == selectOptions)
        {
            SDL_SetTextureColorMod(texture, 255, 0, 0); // Изменение цвета
        }
        else
        {
            SDL_SetTextureColorMod(texture, 255, 255, 255); // Возвращение обычного цвета текста
        }

        SDL_QueryTexture(texture, nullptr, nullptr, &destRect.w, &destRect.h);
        SDL_RenderCopy(renderer, texture, nullptr, &destRect);

        ypos += 30;
    }
}
