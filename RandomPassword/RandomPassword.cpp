#include "RandomPassword.h"
#include "json.h"

int main(int argc, char* argv[])
{
    uint32_t count = 1;
    uint32_t digits = 3;
    bool digitOverride = false;
    uint32_t length = 8;
    uint32_t seed = (uint32_t)time(NULL);
    bool toUpper = true;
    bool jsonLoaded = false;
    PW_TYPE pwType = PW_TYPE::STANDARD;
    std::string customString;
    std::string jsonFileName = "randompassword.json";
    
    if (argc > 0)
    {
        for (int32_t i = 0; i < argc; i++)
        {
            if (strcmp(argv[i], "-?") == 0 || strcmp(argv[i], "/?") == 0)
            {
                if (argc == 3 && strcmp(argv[i + 1], "custom") == 0)
                {
                    std::cout << "Custom password:" << std::endl;
                    std::cout << "    Custom password allows you to specify a random password based on specified expression." << std::endl;
                    std::cout << "    Similar to regular expressions. This type ignores length, lower and d switches." << std::endl;
                    std::cout << std::endl;
                    std::cout << "    Usage: randompassword -t custom \"EXPR\"" << std::endl;
                    std::cout << "        [x-x]        Range of characters e.g. [0-9],[a-z],[a-Z]." << std::endl;
                    std::cout << "        [x]          Type of characters e.g. [vowel],[consonant],[symbol]." << std::endl;
                    std::cout << "                     [VOWEL] and [CONSONANT] will produce an uppercase character." << std::endl;
                    std::cout << "        [word1]      Random word from first array. word1 will produce an lowercase word" << std::endl;
                    std::cout << "                     WORD1 an uppercase word and Word1 a propercase word." << std::endl;
                    std::cout << "        [word2]      Random word from first array. word2 will produce an lowercase word" << std::endl;
                    std::cout << "                     WORD2 an uppercase word and Word2 a propercase word." << std::endl;
                    std::cout << "        x            literial character e.g. abc" << std::endl;
                    std::cout << "        {x}          Character count of range e.g. {3}." << std::endl;
                    std::cout << std::endl;
                    std::cout << "    Example: randompassword -t custom \"[symbol][a-z]{4}[A-Z]{3}[0-9]{2}-[a-Z]{4}[symbol][symbol]\"" << std::endl;
                    std::cout << "             Could generate a password of: !efyrEKS48-GHsR?!" << std::endl;
                    std::cout << std::endl;
                }
                else
                {
                    std::cout << std::endl << "Usage: randompassword [-n count] [-s seed] [-j jsonfile] [[-t type] [-l length] | [-lower] [-d count] | [-generatejson]]" << std::endl << std::endl;
                    std::cout << "Options:" << std::endl;
                    std::cout << "    -n count          Number of passwords to generate." << std::endl;
                    std::cout << "    -t type           Types: standard, o365, gibberish, custom." << std::endl;
                    std::cout << "                      O365 password (3 letters 5 numbers)." << std::endl;
                    std::cout << "                      Gibberish password (Random characters)." << std::endl;
                    std::cout << "                      Custom password (simlar to regex use -? custom for further help)." << std::endl;
                    std::cout << "                      (this switch will cause -lower and -d switches to be ignored)." << std::endl;
                    std::cout << "    -l length         Length of gibberish password." << std::endl;
                    std::cout << "    -lower            Passwords to be all lowercase." << std::endl;
                    std::cout << "    -d count          Digit count in password. (6 limit)." << std::endl;
                    std::cout << "    -s seed           RNG Seed. Uses time by default." << std::endl;
                    std::cout << "    -j jsonfile       Specify a JSON file to use instead of the default \"randompassword.json\"." << std::endl;
                    std::cout << "    -generatejson     Generates a default JSON file." << std::endl;
                    std::cout << std::endl;
                }
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
                else if (strcmp(argv[i + 1], "custom") == 0)
                {
                    if (i + 2 <= argc)
                    {
                        customString = argv[i + 2];
                        pwType = PW_TYPE::CUSTOM;
                    }
                    else
                    {
                        std::cout << "ERROR syntax error with custom password type." << std::endl;
                        return 1;
                    }
                }
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
                std::ofstream jsonFile("randompassword.json", std::ofstream::binary | std::ofstream::trunc);
                if (jsonFile)
                {
                    LPVOID DefaultJSONFilePtr = nullptr;
                    size_t DefaultJSONSize = 0;
                    if (GetInternalJSONPointer(DefaultJSONFilePtr, DefaultJSONSize) == true && DefaultJSONSize > 0)
                    {
                        char* DefaultJSON = new char[DefaultJSONSize + 1];
                        memcpy(DefaultJSON, DefaultJSONFilePtr, DefaultJSONSize);
                        DefaultJSON[DefaultJSONSize] = 0;
                        jsonFile << DefaultJSON;
                        jsonFile.close();
                        delete[] DefaultJSON;
                        std::cout << "randompassword.json created." << std::endl;
                        return 0;
                    }
                    else
                    {
                        std::cout << "ERROR creating randompassword.json." << std::endl;
                        return 1;
                    }
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
    else
    {
        LPVOID DefaultJSONFilePtr = nullptr;
        size_t DefaultJSONSize = 0;
        if (GetInternalJSONPointer(DefaultJSONFilePtr, DefaultJSONSize) == true)
        {
            if (DefaultJSONSize > 0 && DefaultJSONFilePtr != nullptr)
            {
                char* DefaultJSON = new char[DefaultJSONSize + 1];
                memcpy(DefaultJSON, DefaultJSONFilePtr, DefaultJSONSize);
                DefaultJSON[DefaultJSONSize] = 0;
                try {
                    std::stringstream ss(std::string(DefaultJSON, DefaultJSONSize));
                    nlohmann::json json;
                    ss >> json;

                    if (digitOverride == false)
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
                    delete[] DefaultJSON;
                }
                delete[] DefaultJSON;
            }
        }
    }

    srand(seed);

    {
        if (pwType == PW_TYPE::O365)
        {
            std::string expr = "[CONSONANT][vowel][consonant][0-9]{5}";
            GenerateCustomPasswords(expr, count);
        }
        else if (pwType == PW_TYPE::GIBBERISH)
        {
            for (uint32_t i = 0; i < count; i++)
            {
                for (uint32_t j = 0; j < length; j++)
                    std::cout << (char)((rand() % 78) + 48);
                std::cout << std::endl;
            }
        }
        else if (pwType == PW_TYPE::CUSTOM)
        {
            GenerateCustomPasswords(customString, count);
        }
        else
        {
            std::stringstream exprstream;
            if (toUpper)
            {
                exprstream << "[Word1][Word2][0-9]{" << digits << "}[symbol]";
            }
            else
            {
                exprstream << "[word1][word2][0-9]{" << digits << "}[symbol]";
            }
            std::string expr = exprstream.str();
            GenerateCustomPasswords(expr, count);
        }
    }
    return 0;
}
