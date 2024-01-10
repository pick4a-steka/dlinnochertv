#include "filesForRecords.hpp"

filesForRecords::filesForRecords(SDL_Renderer *ren, TTF_Font *mFont)
{
    binfile = "records.bin";
    txtfile = "file_for_print.txt";
    recordText = new TextRender(ren, mFont, {255, 255, 0});
}

bool filesForRecords::vectorIsEmpty()
{
    std::vector<Record> records = readRecords();
    if (records.empty())
        IsEmpty = true;
    else IsEmpty = false;

    return IsEmpty;
}

std::vector<filesForRecords::Record> filesForRecords::readRecords()
{
    std::ifstream file(binfile, std::ios::binary);
    if (!file)
    {
        return {};
    }
    std::vector<Record> records;
    while (true)
    {
        std::string name;
        int score;
        std::size_t nameLen;
        if (!file.read(reinterpret_cast<char*>(&nameLen), sizeof(std::size_t)))
        {
            break;
        }
        name.resize(nameLen);
        if (!file.read(&name[0], nameLen))
        {
            break;
        }
        if (!file.read(reinterpret_cast<char*>(&score), sizeof(int)))
        {
            break;
        }
        records.push_back({name, score});
    }
    file.close();
    return records;
}

void filesForRecords::writeRecords(const std::string& name, int score)
{
    Record record;
    record.name = name; record.score = score;
    std::vector<Record> records = readRecords();
    records.push_back(record);
    std::sort(records.begin(), records.end(), [](const Record& a, const Record& b)
    {
        return a.score > b.score;
    });

    if (records.size() > 10) records.resize(10);

    std::ofstream file(binfile, std::ios::binary | std::ios::trunc);
    if (!file)
    {
        return;
    }

    for (const Record& rec : records)
    {
        std::size_t nameLen = rec.name.length();
        file.write(reinterpret_cast<const char*>(&nameLen), sizeof(std::size_t));
        file.write(rec.name.c_str(), nameLen);
        file.write(reinterpret_cast<const char*>(&rec.score), sizeof(int));
    }

    file.close();
}

void filesForRecords::preparingFileForPrinting()
{
    std::vector<Record> records = readRecords();
    std::ofstream file(txtfile);
    if (!file)
    {
        return;
    }
    file << "<<<<<Records>>>>>\n";
    file << "Name" << std::setw(14) << "Score" << std::endl;
    file << std::setfill('-') << std::setw(18) << "" << std::setfill(' ') << std::endl;
    for (const Record& rec : records)
    {
        file << std::left << std::setw(14) << rec.name << std::left << std::setw(14) << rec.score << std::endl;
    }

    file.close();
}

void filesForRecords::cleanFile()
{
    std::ofstream file(binfile, std::ios::binary | std::ios::trunc);
    if (!file)
    {
        return;
    }

    file.close();
}

bool filesForRecords::executiveMethodRecords(bool& isRunRecord)
{
    int lineHeight = 30, y = HEIGHT / 5;
    SDL_Event event;
    std::vector<Record> records = readRecords();

    for (const Record& rec : records)
    {
        y += lineHeight;
        std::string text1 = rec.name;
        recordText->setText(text1); recordText->setPosition(WIDTH / 7, y); recordText->render();
        std::string text2 = std::to_string(rec.score);
        recordText->setText(text2); recordText->setPosition((WIDTH / 2.7), y); recordText->render();
    }

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            exit(0);
        else if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_e)
            {
                preparingFileForPrinting();
                isRunRecord = false;
                return true;
            }
            else if (event.key.keysym.sym == SDLK_q)
            {
                cleanFile();
                isRunRecord = false;
                return true;
            }
            else if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                isRunRecord = false;
                return false;
            }
        }
    }
}
