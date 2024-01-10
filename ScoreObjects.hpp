#pragma once
#include "Game.hpp"
#include "GameObject.hpp"

class ScoreObjects
{
protected:
    SDL_Texture *Tex_entity;
    SDL_Renderer *ren_entity;
    int windowHeight, windowWidth;
    int xpos;
    int ypos;
    SDL_Rect srcRect, destRect;
    int scoreValue;

    void initializeTexture(const char* TextureName, SDL_Renderer *ren);
    bool interactionManager(int x, int y, int drX, int drY, GameObject* gObj);
public:
    ScoreObjects();
    virtual ~ScoreObjects();

    virtual void randomPosition() = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual bool interaction(GameObject *gObj) = 0;

    int GetScoreValue()
    {
        return scoreValue;
    }
};

class Candle : public ScoreObjects
{
public:
    Candle(const char *TextureName, SDL_Renderer *ren);

    void Update() override;
    void Render() override;
    void randomPosition() override;
    bool interaction(GameObject *gObj) override;
};

class Lamp : public ScoreObjects
{
public:
    Lamp(const char *TextureName, SDL_Renderer *ren);

    void Update() override;
    void Render() override;
    void randomPosition() override;
    bool interaction(GameObject *gObj) override;
};

class Chandelier : public ScoreObjects
{
public:
    Chandelier(const char *TextureName, SDL_Renderer *ren);

    void Update() override;
    void Render() override;
    void randomPosition() override;
    bool interaction(GameObject *gObj) override;
};

class Red_man : public ScoreObjects
{
public:
    Red_man(const char *TextureName, SDL_Renderer *ren);

    void Update() override;
    void Render() override;
    void randomPosition() override;
    bool interaction(GameObject *gObj) override;
};

class Violet_man : public ScoreObjects
{
public:
    Violet_man(const char *TextureName, SDL_Renderer *ren);

    void Update() override;
    void Render() override;
    void randomPosition() override;
    bool interaction(GameObject *gObj) override;
};

class Orange_man : public ScoreObjects
{
public:
    Orange_man(const char *TextureName, SDL_Renderer *ren);

    void Update() override;
    void Render() override;
    void randomPosition() override;
    bool interaction(GameObject *gObj) override;
};
