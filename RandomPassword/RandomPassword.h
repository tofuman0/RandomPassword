#pragma once
#include <iostream>
#include <time.h>
#include <fstream>
#include <Windows.h>
#include <vector>


const enum class PW_TYPE {
	STANDARD,
	O365,
	GIBBERISH,
	CUSTOM
};
const enum class PW_ELEMENT_TYPE {
	ALPHA,
	NUMERIC,
	VOWEL,
	CONSONANT,
	SYMBOL,
	LITERIAL,
	WORD1,
	WORD2
};
std::vector<std::string> FirstWords{
	"red",
	"yellow",
	"green",
	"blue",
	"orange",
	"purple",
	"pink"
};
std::vector<std::string> SecondWords{
	"alligator",
	"anaconda",
	"aphid",
	"badger",
	"barracuda",
	"bass",
	"bat",
	"bear",
	"beaver",
	"bee",
	"beetle",
	"bird",
	"bobcat",
	"buffalo",
	"butterfly",
	"buzzard",
	"camel",
	"caribou",
	"carp",
	"cat",
	"caterpillar",
	"catfish",
	"cheetah",
	"chicken",
	"cobra",
	"condor",
	"cougar",
	"coyote",
	"cricket",
	"crocodile",
	"crow",
	"deer",
	"dinosaur",
	"dolphin",
	"dove",
	"dragonfly",
	"duck",
	"eagle",
	"elephant",
	"emu",
	"falcon",
	"ferret",
	"finch",
	"fish",
	"flamingo",
	"fox",
	"frog",
	"goat",
	"goose",
	"gopher",
	"gorilla",
	"grasshopper",
	"hamster",
	"hare",
	"hawk",
	"horse",
	"kangaroo",
	"leopard",
	"lion",
	"lizard",
	"llama",
	"lobster",
	"mongoose",
	"monkey",
	"moose",
	"mosquito",
	"mouse",
	"octopus",
	"orca",
	"ostrich",
	"otter",
	"owl",
	"oyster",
	"panda",
	"parrot",
	"peacock",
	"pelican",
	"penguin",
	"perch",
	"pheasant",
	"pigeon",
	"quail",
	"rabbit",
	"raccoon",
	"rat",
	"rattlesnake",
	"raven",
	"rooster",
	"sheep",
	"shrew",
	"skunk",
	"snail",
	"snake",
	"spider",
	"tiger",
	"walrus",
	"whale",
	"wolf",
	"zebra"
};
std::vector<std::string> Symbols {
	"!",
	"?",
	"%",
	"#"
};
std::vector<std::string> jsonFirst;
std::vector<std::string> jsonSecond;
std::vector<std::string> jsonSymbols;


std::string toLower(std::string& in)
{
	std::string lowercase;
	lowercase.resize(in.length());
	uint32_t i = 0;
	for (i = 0; i < in.length(); i++)
	{
		lowercase[i] = ::tolower(in[i]);
	}
	return lowercase;
}
std::string toUpper(std::string& in)
{
	std::string uppercase;
	uppercase.resize(in.length());
	uint32_t i = 0;
	for (i = 0; i < in.length(); i++)
	{
		uppercase[i] = ::toupper(in[i]);
	}
	return uppercase;
}
std::vector<std::string> explode(std::string& in, const std::string& delimiter)
{
	std::vector<std::string> tokens(0);
	char* token = nullptr, * buffer = nullptr;
	token = strtok_s((char*)in.c_str(), delimiter.c_str(), &buffer);
	while (token)
	{
		tokens.push_back(token);
		token = strtok_s(NULL, delimiter.c_str(), &buffer);
	}

	return tokens;
}
void GenerateCustomPasswords(std::string& expr, uint32_t count, bool usejson)
{
	typedef struct stElement {
		PW_ELEMENT_TYPE type;
		std::string value;
		bool uppercase;
		uint32_t count;
	} Element;
	std::vector<Element> elements;
	uint32_t exprOffset = 0;

	while (exprOffset < expr.length())
	{
		std::string token;
		uint32_t offset = 0;
		if ((offset = expr.find('[', exprOffset)) != std::string::npos)
		{
			if (offset > 0)
			{
				token = expr.substr(exprOffset, offset - exprOffset);
				Element thisElement = {
						PW_ELEMENT_TYPE::LITERIAL,
						token,
						false,
						1
				};
				elements.push_back(thisElement);
			}
			
			exprOffset = offset + 1;
			if ((offset = expr.find(']', exprOffset)) != std::string::npos)
			{
				uint32_t elementCount = 1;
				std::string element = expr.substr(exprOffset, offset - exprOffset);
				if (expr.substr(offset + 1, 1) == "{")
				{
					if(expr.find('}', exprOffset) != std::string::npos)
					{
						elementCount = atoi(expr.substr(offset + 2, expr.find('}', exprOffset)).c_str());
						exprOffset = expr.find('}', exprOffset) + 1;
					}
				}
				else
				{
					exprOffset = offset + 1;
				}

				if (element == "vowel")
				{
					Element thisElement = {
						PW_ELEMENT_TYPE::VOWEL,
						std::string(),
						false,
						elementCount
					};
					elements.push_back(thisElement);
				}
				else if (element == "VOWEL")
				{
					Element thisElement = {
						PW_ELEMENT_TYPE::VOWEL,
						std::string(),
						true,
						elementCount
					};
					elements.push_back(thisElement);
				}
				else if (element == "consonant")
				{
					Element thisElement = {
						PW_ELEMENT_TYPE::CONSONANT,
						std::string(),
						false,
						elementCount
					};
					elements.push_back(thisElement);
				}
				else if (element == "CONSONANT")
				{
					Element thisElement = {
						PW_ELEMENT_TYPE::CONSONANT,
						std::string(),
						true,
						elementCount
					};
					elements.push_back(thisElement);
				}
				else if (element == "symbol" || element == "SYMBOL")
				{
					Element thisElement = {
						PW_ELEMENT_TYPE::SYMBOL,
						std::string(),
						false,
						elementCount
					};
					elements.push_back(thisElement);
				}
				else if (element == "word1")
				{
					Element thisElement = {
						PW_ELEMENT_TYPE::WORD1,
						std::string(),
						false,
						elementCount
					};
					elements.push_back(thisElement);
				}
				else if (element == "WORD1")
				{
					Element thisElement = {
						PW_ELEMENT_TYPE::WORD1,
						std::string(),
						true,
						elementCount
					};
					elements.push_back(thisElement);
				}
				else if (element == "word2")
				{
					Element thisElement = {
						PW_ELEMENT_TYPE::WORD2,
						std::string(),
						false,
						elementCount
					};
					elements.push_back(thisElement);
				}
				else if (element == "WORD2")
				{
					Element thisElement = {
						PW_ELEMENT_TYPE::WORD2,
						std::string(),
						true,
						elementCount
					};
					elements.push_back(thisElement);
				}
				else
				{
					if (element.find('-', 0) != std::string::npos)
					{
						if (::isalpha(element.c_str()[0]))
						{
							Element thisElement = {
								PW_ELEMENT_TYPE::ALPHA,
								element,
								false,
								elementCount
							};
							elements.push_back(thisElement);
						}
						else if (::isdigit(element.c_str()[0]))
						{
							Element thisElement = {
								PW_ELEMENT_TYPE::NUMERIC,
								element,
								false,
								elementCount
							};
							elements.push_back(thisElement);
						}
					}
				}
			}
		}
		else
		{
			token = expr.substr(exprOffset, expr.length() - exprOffset);
			Element thisElement = {
				PW_ELEMENT_TYPE::LITERIAL,
				token,
				false,
				1
			};
			elements.push_back(thisElement);
			break;
		}
	}

	for (auto& element : elements)
	{
		switch (element.type)
		{
			case PW_ELEMENT_TYPE::ALPHA:
			{
				char alpha[]{ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
				std::vector<std::string> tokens = explode(element.value, "-");
				if (tokens.size() == 2)
				{
					auto findOffset = [&](char character) -> int32_t
					{
						for (int32_t i = 0; i < sizeof(alpha); i++)
						{
							if (alpha[i] == character)
								return i;
						}
						return -1;
					};

					int32_t offset1 = findOffset(tokens[0].c_str()[0]);
					int32_t offset2 = findOffset(tokens[1].c_str()[0]);
					if (offset1 != -1 && offset2 != -1 && offset1 < offset2)
					{
						for (uint32_t i = 0; i < element.count; i++)
							std::cout << alpha[((rand() % (offset2 - offset1)) + offset1)];
					}
				}
				break;
			}
			case PW_ELEMENT_TYPE::NUMERIC:
			{
				std::vector<std::string> tokens = explode(element.value, "-");
				if (tokens.size() == 2 && ::isdigit(tokens[0][0]) && ::isdigit(tokens[1][0]))
				{
					uint32_t fromValue = atoi(tokens[0].c_str());
					uint32_t toValue = atoi(tokens[1].c_str()) + 1;
					if (fromValue < toValue)
					{
						for (uint32_t i = 0; i < element.count; i++)
							std::cout << ((rand() % (toValue - fromValue)) + fromValue);
					}
				}
				break;
			}
			case PW_ELEMENT_TYPE::VOWEL:
			{
				char vowels[]{ 'a', 'e', 'i', 'o', 'u' };
				for (uint32_t i = 0; i < element.count; i++)
					std::cout << (char)(element.uppercase ? vowels[rand() % sizeof(vowels)] - 32 : vowels[rand() % sizeof(vowels)]);
				break;
			}
			case PW_ELEMENT_TYPE::CONSONANT:
			{
				char consonants[]{ 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z' };

				for (uint32_t i = 0; i < element.count; i++)
					std::cout << (char)(element.uppercase ? consonants[rand() % sizeof(consonants)] - 32 : consonants[rand() % sizeof(consonants)]);
				break;
			}
			case PW_ELEMENT_TYPE::SYMBOL:
			{
				if (usejson)
				{
					for (uint32_t i = 0; i < element.count; i++)
						std::cout << jsonSymbols[rand() % jsonSymbols.size()];
					break;
				}
				else
				{
					for (uint32_t i = 0; i < element.count; i++)
						std::cout << Symbols[rand() % Symbols.size()];
					break;
				}
			}
			case PW_ELEMENT_TYPE::LITERIAL:
			{
				for (uint32_t i = 0; i < element.count; i++)
					std::cout << element.value;
				break;
			}
			case PW_ELEMENT_TYPE::WORD1:
			{
				if (usejson)
				{
					for (uint32_t i = 0; i < element.count; i++)
					{
						std::string word = element.uppercase ? toUpper(jsonFirst[rand() % jsonFirst.size()]) : jsonFirst[rand() % jsonFirst.size()];
						std::cout << word;
					}
					break;
				}
				else
				{
					for (uint32_t i = 0; i < element.count; i++)
					{
						std::string word = element.uppercase ? toUpper(FirstWords[rand() % FirstWords.size()]) : FirstWords[rand() % FirstWords.size()];
						std::cout << word;
					}
					break;
				}
			}
			case PW_ELEMENT_TYPE::WORD2:
			{
				if (usejson)
				{
					for (uint32_t i = 0; i < element.count; i++)
					{
						std::string word = element.uppercase ? toUpper(jsonSecond[rand() % jsonSecond.size()]) : jsonSecond[rand() % jsonSecond.size()];
						std::cout << word;
					}
					break;
				}
				else
				{
					for (uint32_t i = 0; i < element.count; i++)
					{
						std::string word = element.uppercase ? toUpper(SecondWords[rand() % SecondWords.size()]) : SecondWords[rand() % SecondWords.size()];
						std::cout << word;
					}
					break;
				}
			}
			default:
			{
				for(uint32_t i = 0; i < element.count; i++)
					std::cout << "?";
				break;
			}
		}
	}
}