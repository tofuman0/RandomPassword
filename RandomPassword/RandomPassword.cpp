#include "RandomPassword.h"
#include <iostream>
#include <time.h>
#include <fstream>
#include "json.h"

const enum class PW_TYPE {
    STANDARD,
    O365,
    GIBBERISH
};

int main(int argc, char* argv[])
{
    uint32_t count = 1;
    uint32_t digits = 3;
    uint32_t digitsValue = 0;
    uint32_t digitsOffset = 0;
    bool digitOverride = false;
    uint32_t length = 8;
    uint32_t seed = (uint32_t)time(NULL);
    bool toUpper = true;
    bool jsonLoaded = false;
    PW_TYPE pwType = PW_TYPE::STANDARD;
    std::string jsonFileName = "randompassword.json";
    
    if (argc > 0)
    {
        for (int32_t i = 0; i < argc; i++)
        {
            if (strcmp(argv[i], "-?") == 0 || strcmp(argv[i], "/?") == 0)
            {
                std::cout << std::endl << "Usage: randompassword [-n count] [-s seed] [-j jsonfile] [[-t type] [-l length] | [-lower] [-d count] | [-generatejson]]" << std::endl << std::endl;
                std::cout << "Options:" << std::endl;
                std::cout << "    -n count          Number of passwords to generate." << std::endl;
                std::cout << "    -t type           Types: standard, o365, gibberish." << std::endl;
                std::cout << "                      O365 password (3 letters 5 numbers)." << std::endl;
                std::cout << "                      Gibberish password (Random characters)." << std::endl;
                std::cout << "                      (this switch will cause -lower and -d switches to be ignored)." << std::endl;
                std::cout << "    -l length         Length of gibberish password." << std::endl;
                std::cout << "    -lower            Passwords to be all lowercase." << std::endl;
                std::cout << "    -d count          Digit count in password. (6 limit)." << std::endl;
                std::cout << "    -s seed           RNG Seed. Uses time by default." << std::endl;
                std::cout << "    -j jsonfile       Specify a JSON file to use instead of the default \"randompassword.json\"." << std::endl;
                std::cout << "    -generatejson     Generates a default JSON file." << std::endl;
                std::cout << std::endl;
                return 0;
            }
            else if ((strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "/n") == 0) && argc > 2)
            {
                int32_t getCount = atoi(argv[i + 1]);
                if (getCount > 0)
                {
                    count = getCount;
                    i++;
                }
            }
            else if ((strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "/t") == 0) && argc > 2)
            {
                if (strcmp(argv[i + 1], "o365") == 0)
                    pwType = PW_TYPE::O365;
                else if (strcmp(argv[i + 1], "gibberish") == 0)
                    pwType = PW_TYPE::GIBBERISH;
                else
                    pwType = PW_TYPE::STANDARD;
            }
            else if ((strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "/l") == 0) && argc > 2)
            {
                int32_t getLength = atoi(argv[i + 1]);
                if (getLength > 0)
                {
                    length = getLength;
                    i++;
                }
            }
            else if ((strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "/s") == 0) && argc > 2)
            {
                uint32_t getSeed = atoi(argv[i + 1]);
                seed = getSeed;
                i++;
            }
            else if ((strcmp(argv[i], "-j") == 0 || strcmp(argv[i], "/j") == 0) && argc > 2)
            {
                jsonFileName = argv[i + 1];
                i++;
            }
            else if ((strcmp(argv[i], "-generatejson") == 0 || strcmp(argv[i], "/generatejson") == 0) && argc == 2)
            {
                std::ofstream jsonFile("randompassword.json", std::ofstream::trunc);
                if (jsonFile)
                {
                    jsonFile << DefaultJSON;
                    jsonFile.close();
                    std::cout << "randompassword.json created." << std::endl;
                    return 0;
                }
                else
                {
                    std::cout << "ERROR creating randompassword.json." << std::endl;
                    return 1;
                }
            }
            else if ((strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "/d") == 0) && argc > 2)
            {
                int32_t getCount = atoi(argv[i + 1]);
                if (getCount < 0)
                    getCount = 0;
                else if (getCount > 6)
                getCount = 6;
                digits = getCount;
                digitOverride = true;
                i++;
            }
            else if ((strcmp(argv[i], "-lower") == 0 || strcmp(argv[i], "/lower") == 0) && argc > 1)
            {
                toUpper = false;
            }
        }
    }

    std::vector<std::string> jsonFirst;
    std::vector<std::string> jsonSecond;
    std::vector<std::string> jsonSymbols;

    std::ifstream jsonfile(jsonFileName, std::ifstream::binary);
    if (jsonfile)
    {
        try {
            nlohmann::json json;
            jsonfile >> json;
            jsonfile.close();

            if(digitOverride == false)
                digits = json["digits"].get<int>();
            for (auto& jsonFirstEntry : json["first"])
            {
                jsonFirst.push_back(jsonFirstEntry);
            }
            for (auto& jsonSecondEntry : json["second"])
            {
                jsonSecond.push_back(jsonSecondEntry);
            }
            for (auto& jsonSymbolsEntry : json["symbols"])
            {
                jsonSymbols.push_back(jsonSymbolsEntry);
            }

            if (jsonFirst.size() > 0 && jsonSecond.size() > 0 && jsonSymbols.size() > 0)
                jsonLoaded = true;
        }
        catch (nlohmann::json::exception ex)
        {
            std::cout << "Error: " << ex.what() << std::endl;
        }
    }

    switch (digits)
    {
    case 1:
        digitsValue = 10;
        digitsOffset = 0;
        break;
    case 2:
        digitsValue = 90;
        digitsOffset = 10;
        break;
    case 3:
        digitsValue = 900;
        digitsOffset = 100;
        break;
    case 4:
        digitsValue = 9000;
        digitsOffset = 1000;
        break;
    case 5:
        digitsValue = 90000;
        digitsOffset = 10000;
        break;
    case 6:
        digitsValue = 900000;
        digitsOffset = 100000;
        break;
    default:
        digitsValue = 0;
        digitsOffset = 0;
        break;
    }
    srand(seed);
    for (uint32_t i = 0; i < count; i++)
    {
        uint32_t first = 0;
        uint32_t second = 0;
        uint32_t third = 0;
        uint32_t fourth = 0;
        char strings[3][100] = { 0 };
        if (pwType == PW_TYPE::O365)
        {
            char vowels[]{ 'a', 'e', 'i', 'o', 'u' };
            char consonants[]{ 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z' };
            std::cout << (char)(consonants[rand() % sizeof(consonants)] - 32) << (char)(vowels[(rand() % sizeof(vowels))]) << (char)(consonants[rand() % sizeof(consonants)]) << (rand() % 10) << (rand() % 10) << (rand() % 10) << (rand() % 10) << (rand() % 10) << "\n";
        }
        else if (pwType == PW_TYPE::GIBBERISH)
        {
            for(uint32_t i = 0; i < length; i++)
                std::cout << (char)((rand() % 78) + 48);
            std::cout << std::endl;
        }
        else
        {
            if (jsonLoaded)
            {
                first = rand() % (jsonFirst.size());
                second = rand() % (jsonSecond.size());
                third = rand();
                fourth = rand() % (jsonSymbols.size());
                strcpy_s(&strings[0][0], 100, jsonFirst[first].c_str());
                strcpy_s(&strings[1][0], 100, jsonSecond[second].c_str());
                strcpy_s(&strings[2][0], 100, jsonSymbols[fourth].c_str());
            }
            else
            {
                first = rand() % (sizeof(FirstWords) / sizeof(const char*));
                second = rand() % (sizeof(SecondWords) / sizeof(const char*));
                third = rand();
                fourth = rand() % (sizeof(Symbols) / sizeof(const char*));
                strcpy_s(&strings[0][0], 100, FirstWords[first]);
                strcpy_s(&strings[1][0], 100, SecondWords[second]);
                strcpy_s(&strings[2][0], 100, Symbols[fourth]);
            }

            if (digits)
            {
                third %= digitsValue;
                third += digitsOffset;
            }

            if (toUpper)
            {
                strings[0][0] = toupper(strings[0][0]);
                strings[1][0] = toupper(strings[1][0]);
            }
            if (digits)
                std::cout << strings[0] << strings[1] << third << strings[2] << "\n";
            else
                std::cout << strings[0] << strings[1] << strings[2] << "\n";
        }
    }
    return 0;
}
