#include "ObjectManager.hpp"
#include "ScoreObjects.hpp"
#include "Counter.hpp"

ObjectManager::~ObjectManager()
{
    clearObjects();
}

void ObjectManager::clearObjects()
{
    objects.clear();
}

void ObjectManager::addLamp(int count, SDL_Renderer *ren)
{
    for (int i = 0; i < count; i++)
    {
        auto lamp = std::make_unique<Lamp>("passive/lamp.png", ren);
        lamp->randomPosition();
        objects.push_back(std::move(lamp)); // Функция std::move преобразует объект lamp в "состояние перемещения"
    }
}

void ObjectManager::addCandle(int count, SDL_Renderer *ren)
{
    for (int i = 0; i < count; i++)
    {
        auto candle = std::make_unique<Candle>("passive/candle.png", ren);
        candle->randomPosition();
        objects.push_back(std::move(candle));
    }
}

void ObjectManager::addChandelier(int count, SDL_Renderer *ren)
{
    for (int i = 0; i < count; i++)
    {
        auto chandelier = std::make_unique<Chandelier>("passive/chandelier.png", ren);
        chandelier->randomPosition();
        objects.push_back(std::move(chandelier));
    }
}

void ObjectManager::addRedMan(int count, SDL_Renderer *ren)
{
    for (int i = 0; i < count; i++)
    {
        auto red_man = std::make_unique<Red_man>("passive/red_man.png", ren);
        red_man->randomPosition();
        objects.push_back(std::move(red_man));
    }
}

void ObjectManager::addVioletMan(int count, SDL_Renderer *ren)
{
    for (int i = 0; i < count; i++)
    {
        auto violet_man = std::make_unique<Violet_man>("passive/violet_man.png", ren);
        violet_man->randomPosition();
        objects.push_back(std::move(violet_man));
    }
}

void ObjectManager::addOrangeMan(int count, SDL_Renderer *ren)
{
    for (int i = 0; i < count; i++)
    {
        auto orange_man = std::make_unique<Orange_man>("passive/orange_man.png", ren);
        orange_man->randomPosition();
        objects.push_back(std::move(orange_man));
    }
}

int ObjectManager::update(GameObject *MainObject, ScoreCounter *cntObject)
{
    for (const auto& object : objects)
    {
        object->Update();

        if (object->interaction(MainObject))
        {
            auto scoreObject = dynamic_cast<ScoreObjects*>(object.get());
            int scoreValue = scoreObject->GetScoreValue();
            cntObject->update(scoreValue);
            for (const auto& ob : objects)
            {
                ob->randomPosition();
            }
        }
    }
    return cntObject->GetScore();
}

void ObjectManager::render()
{
    for (const auto& object : objects)
    {
        object->Render();
    }
}
