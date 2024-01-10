#include "Game.hpp"
#include "ConstantsSize.h"
#include "initWindow.hpp"
#include "TextRender.hpp"
#include "Menu.hpp"
#include "filesForRecords.hpp"
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>

bool controlButton(bool process);

int main(int argc, char *argv[])
{
    Game *game = nullptr;
    initWindow *mainWindow = nullptr;
    const int FPS = 60; // число 60 наиболее близко к частоте обновления кадров монитора
    const int FrameDelay = 1000 / FPS; // Время между кадрами

    Uint32 frameStart; // Начало кадра
    int frameTime; // Время кадра

    srand(time(0));

    game = new Game();
    mainWindow = new initWindow();
    mainWindow->init("Dlinnochert", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, false);
    TextRender textOnWindow(mainWindow->GetRenderer(), mainWindow->GetFont(), {255, 255, 255});
    textOnWindow.setText("Kolmogorov Mikhail, group O729B");
    textOnWindow.setPosition(WIDTH / 4, HEIGHT / 2);
    mainWindow->changeBack("passive/splash_screen.png");
    mainWindow->renderBack();
    textOnWindow.render();
    SDL_RenderPresent(mainWindow->GetRenderer());
    SDL_Delay(3000);

    bool isInputPlayerName = true;
    bool isHelp = false;
    bool isRecord = false;
    bool isResultGame = false;
    bool isStartGame = false;
    bool enteringPlayerName = true;
    int points;
    std::string playerName;
    Menu menu(mainWindow->GetRenderer(), mainWindow->GetFont());
    filesForRecords workWithRecords(mainWindow->GetRenderer(), mainWindow->GetFont());

    while (mainWindow->mainRunning())
    {
        mainWindow->isCloseWindow();
        if (isInputPlayerName)
        {
            mainWindow->changeBack("passive/menu_screen.png");
            playerName = "";
            SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
            SDL_StartTextInput(); // Включаем режим ввода текста

            while (enteringPlayerName)
            {
                SDL_Event event;
                SDL_RenderClear(mainWindow->GetRenderer());
                mainWindow->renderBack();
                textOnWindow.setText("Enter your name:");
                textOnWindow.setPosition(WIDTH / 3, HEIGHT / 5);
                textOnWindow.render();
                SDL_RenderPresent(mainWindow->GetRenderer());

                while (SDL_PollEvent(&event))
                {
                    if (event.type == SDL_TEXTINPUT)
                    {
                        if (playerName.length() < 12) // Максимальная длина имени 12 символов
                            playerName += event.text.text; // Добавление символа в имя игрока
                    }
                    else if (event.type == SDL_KEYDOWN)
                    {
                        if (event.key.keysym.sym == SDLK_RETURN)
                        {
                            if (!playerName.empty())
                                enteringPlayerName = false; // Пользователь нажал Enter, завершение ввода имени
                        }
                        else if (event.key.keysym.sym == SDLK_BACKSPACE && !playerName.empty())
                        {
                            playerName.pop_back(); // Удаление последнего символа из имени игрока
                        }
                    }
                    else if (event.type == SDL_QUIT)
                    {
                        exit(0);
                    }
                }

                // Отображение имени игрока на экране
                textOnWindow.setText(playerName);
                textOnWindow.setPosition(WIDTH / 3, (HEIGHT / 5) + 20);
                textOnWindow.render();
                SDL_RenderPresent(mainWindow->GetRenderer());
                SDL_Delay(FrameDelay);
            }
            SDL_StopTextInput(); // Отключение режима ввода текста
            enteringPlayerName = true; menu.giveMenu();
        }

        if (menu.IsRunMenu())
        {
            mainWindow->changeBack("passive/menu_screen.png");
            menu.createMenu();
            while (menu.IsRunMenu())
            {
                SDL_RenderClear(mainWindow->GetRenderer());
                mainWindow->renderBack();
                menu.handleEvents();
                menu.render();
                SDL_RenderPresent(mainWindow->GetRenderer());
                SDL_Delay(FrameDelay);
            }
            isInputPlayerName = menu.changePlayer();
            isHelp = menu.IsHelpDemonstration();
            isRecord = menu.IsRecordsMenu();
            isStartGame = menu.startGame();
            menu.cleanMenu(); menu.ProcessReset();
        }

        if (isHelp)
        {
            mainWindow->changeBack("passive/menu_screen.png");
            TextRender note(mainWindow->GetRenderer(), mainWindow->GetFont(), {255, 215, 0}); // золотой цвет
            std::string text = "A monster named Dlinnochertv lives in a cave and\ndespite his dark nature, he loves glowing objects.\nBut people are afraid of him, so he doesn't like\npeople. Sometimes Dlinnochertv comes out of\nthe cave in order to replenish the stocks of\nglowing objects. In 60 seconds you need to score as\nmany points as possible. For a light bulb 5 points,\nfor a candle 10 points, for a chandelier\n15 points. Any meeting with people take\naway 5 points.\n\nTap on [ESC] to arrive in main menu";
            while (isHelp)
            {
                SDL_SetRenderDrawColor(mainWindow->GetRenderer(), 0, 0, 0, 255); // Очистить рендерер черным цветом
                SDL_RenderClear(mainWindow->GetRenderer());
                mainWindow->renderBack();
                std::stringstream ss(text);
                std::string line;
                int lineHeight = 30;
                int y = HEIGHT / 5;
                while (std::getline(ss, line))
                {
                    note.setText(line);
                    note.setPosition(WIDTH / 8, y);
                    note.render();
                    y += lineHeight;
                }
                SDL_RenderPresent(mainWindow->GetRenderer());
                isHelp = controlButton(isHelp); SDL_Delay(FrameDelay);
            }
            menu.giveMenu();
        }

        if (isRecord)
        {
            mainWindow->changeBack("passive/menu_screen.png");
            TextRender recordText(mainWindow->GetRenderer(), mainWindow->GetFont(), {255, 255, 0});
            bool isDone;
            if (!workWithRecords.vectorIsEmpty())
            {
                while (isRecord)
                {
                    SDL_RenderClear(mainWindow->GetRenderer());
                    mainWindow->renderBack();
                    recordText.setText("Player:              Score:"); recordText.setPosition(WIDTH / 7, HEIGHT / 6); recordText.render();
                    recordText.setText("ESC->menu");
                    recordText.setPosition(WIDTH / 32, 0); recordText.render();
                    recordText.setText("E->preparing a file for printing Q->delete records"); recordText.setPosition(WIDTH / 32, HEIGHT - 30);
                    recordText.render();
                    isDone = workWithRecords.executiveMethodRecords(isRecord);
                    SDL_RenderPresent(mainWindow->GetRenderer());
                    SDL_Delay(FrameDelay);
                    if (isDone)
                    {
                        recordText.setText("Done!"); recordText.setPosition(WIDTH / 2, HEIGHT / 5); recordText.render();
                    }
                }
            }
            else
            {
                while (isRecord)
                {
                    SDL_RenderClear(mainWindow->GetRenderer());
                    mainWindow->renderBack();
                    recordText.setText("Sorry, there are no records"); recordText.setPosition(WIDTH / 5, HEIGHT / 5); recordText.render();
                    recordText.setText("ESC->menu"); recordText.setPosition(0, 0); recordText.render();
                    SDL_RenderPresent(mainWindow->GetRenderer());
                    isRecord = controlButton(isRecord); SDL_Delay(FrameDelay);
                }
            }
            while (isDone)
            {
                SDL_RenderClear(mainWindow->GetRenderer());
                mainWindow->renderBack();
                recordText.setText("ESC->menu"); recordText.setPosition(WIDTH / 32, 0); recordText.render();
                recordText.setText("Done!"); recordText.setPosition(WIDTH / 2, HEIGHT / 5); recordText.render();
                SDL_RenderPresent(mainWindow->GetRenderer());
                isDone = controlButton(isDone); SDL_Delay(FrameDelay);
            }
            menu.giveMenu();
        }

        if (isStartGame)
        {
            mainWindow->changeBack("passive/map_640.png");
            game->initMobs(mainWindow->GetRenderer(), mainWindow->GetFont());
            bool isGamePause = false, isGameOver = true;
            while (game->processGame())
            {
                frameStart = SDL_GetTicks(); // Возвращает количество милисекунд прошедшее с момента инициализации библиотеки.
                SDL_RenderClear(mainWindow->GetRenderer());
                mainWindow->renderBack();
                game->handleEvents(isGamePause, isGameOver);
                mainWindow->isCloseWindow();
                if (!mainWindow->mainRunning())
                    exit(0);

                game->update(isGamePause);
                game->render();
                textOnWindow.setText(playerName); textOnWindow.setPosition(WIDTH / 2.5, 0); textOnWindow.render();
                if (isGamePause)
                {
                    textOnWindow.setText("The game is on pause"); textOnWindow.setPosition(WIDTH / 3, HEIGHT / 2.5); textOnWindow.render();
                    textOnWindow.setText("BACKSPACE->menu"); textOnWindow.setPosition(WIDTH / 3, (HEIGHT / 2.5) + 30); textOnWindow.render();
                    textOnWindow.setText("ESC->return game"); textOnWindow.setPosition(WIDTH / 3, (HEIGHT / 2.5) + 60); textOnWindow.render();
                }

                SDL_RenderPresent(mainWindow->GetRenderer());
                frameTime = SDL_GetTicks() - frameStart; // Расчет задержки между кадрами, чтобы определить, сколько кадров должно быть выведено каждую секунду
                if (FrameDelay > frameTime)// Проверим, нужно ли будет производить задержку со седующим кадром
                {
                    SDL_Delay(FrameDelay - frameTime);
                }
            }
            game->reset(); isStartGame = false;
            menu.giveMenu();
            points = game->GetScore();
            if (isGameOver)
            {
                workWithRecords.writeRecords(playerName, points);
                isResultGame = true;
            }
        }

        if (isResultGame)
        {
            mainWindow->changeBack("passive/menu_screen.png");
            while (isResultGame)
            {
                SDL_RenderClear(mainWindow->GetRenderer());
                mainWindow->renderBack();
                textOnWindow.setText("Game Result:"); textOnWindow.setPosition(WIDTH / 3, HEIGHT / 8); textOnWindow.render();
                std::string text = "Name: " + playerName;
                textOnWindow.setText(text); textOnWindow.setPosition(WIDTH / 3, (HEIGHT / 8) + 30); textOnWindow.render();
                std::string text2 = "Score: " + std::to_string(points);
                textOnWindow.setText(text2); textOnWindow.setPosition(WIDTH / 3, (HEIGHT / 8) + 60); textOnWindow.render();
                SDL_RenderPresent(mainWindow->GetRenderer());
                isResultGame = controlButton(isResultGame); SDL_Delay(FrameDelay);
            }
        }
    }

    mainWindow->clean();

    return 0;
}

bool controlButton(bool process)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
            process = false;
        if (event.type == SDL_QUIT)
            exit(0);
    }
    return process;
}
