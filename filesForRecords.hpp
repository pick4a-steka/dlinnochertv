#pragma once
#include "Game.hpp"
#include "TextRender.hpp"
#include "ConstantsSize.h"
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <string>

class filesForRecords
{
private:
    std::string binfile, txtfile;
    struct Record
    {
        std::string name;
        int score;
    };
    std::vector<Record> readRecords();
    void preparingFileForPrinting();
    void cleanFile();
    bool IsEmpty;
    TextRender *recordText = nullptr;
public:
    filesForRecords(SDL_Renderer *ren, TTF_Font *mFont);
    void writeRecords(const std::string& name, int score);
    bool executiveMethodRecords(bool& isRunRecord);
    bool vectorIsEmpty();
};
