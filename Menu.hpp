#pragma once
#include "Game.hpp"
#include <vector>

class Menu
{
private:
    SDL_Renderer *renderer;
    TTF_Font *font;
    std::vector<SDL_Texture*> optionsTextures;
    int selectOptions;
    bool IsStartGame;
    bool IsChangePlayer;
    bool menuRunning;
    bool helpDemonstration;
    bool isRecords;

    void quitGame()
    {
        std::cout << "Game over" << std::endl;
        exit(0);
    }

    SDL_Texture* createTextTexture(const std::string &text);
    void handleKeyDown(SDL_Keycode key);
    void handleOptionsSelected(int option);
    void handleMouseClick(int x, int y);
    void handleMouseMotion(int x, int y);
public:
    Menu (SDL_Renderer *mRenderer, TTF_Font *mFont);
    ~Menu ();

    void handleEvents();
    void render();
    void cleanMenu();
    void createMenu();
    bool startGame()
    {
        return IsStartGame;
    }
    bool changePlayer()
    {
        return IsChangePlayer;
    }
    bool IsRunMenu()
    {
        return menuRunning;
    }
    bool IsHelpDemonstration()
    {
        return helpDemonstration;
    }
    void giveMenu()
    {
        menuRunning = true;
    }
    bool IsRecordsMenu()
    {
        return isRecords;
    }
    void ProcessReset();
};

