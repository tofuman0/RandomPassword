#pragma once
#include "resource.h"
#include <iostream>
#include <time.h>
#include <fstream>
#include <Windows.h>
#include <vector>
#include <sstream>

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
const enum class CASE_TYPE {
	NA,
	LOWER,
	UPPER,
	PROPER
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
std::string toProper(std::string& in)
{
	std::string propercase;
	propercase.resize(in.length());
	uint32_t i = 0;
	for (i = 0; i < in.length(); i++)
	{
		if(i == 0)
			propercase[i] = ::toupper(in[i]);
		else
			propercase[i] = ::tolower(in[i]);
	}
	return propercase;
}
std::vector<std::string> explode(std::string in, const std::string& delimiter)
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
bool GetInternalJSONPointer(LPVOID& BufferPtr, size_t& size)
{
	HRSRC res = FindResource(NULL, MAKEINTRESOURCE(IDR_JSON), L"JSON");
	if (res)
	{
		HGLOBAL DefaultJSONFile = LoadResource(NULL, res);
		if (DefaultJSONFile)
		{
			BufferPtr = LockResource(DefaultJSONFile);
			size = SizeofResource(NULL, res);
			return true;
		}
		else
			return false;
	}
	else
		return false;
}
void GenerateCustomPasswords(std::string& expr, uint32_t count)
{
	typedef struct stElement {
		PW_ELEMENT_TYPE type;
		std::string value;
		CASE_TYPE casetype;
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
						CASE_TYPE::NA,
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
						CASE_TYPE::LOWER,
						elementCount
					};
					elements.push_back(thisElement);
				}
				else if (element == "VOWEL")
				{
					Element thisElement = {
						PW_ELEMENT_TYPE::VOWEL,
						std::string(),
						CASE_TYPE::UPPER,
						elementCount
					};
					elements.push_back(thisElement);
				}
				else if (element == "consonant")
				{
					Element thisElement = {
						PW_ELEMENT_TYPE::CONSONANT,
						std::string(),
						CASE_TYPE::LOWER,
						elementCount
					};
					elements.push_back(thisElement);
				}
				else if (element == "CONSONANT")
				{
					Element thisElement = {
						PW_ELEMENT_TYPE::CONSONANT,
						std::string(),
						CASE_TYPE::UPPER,
						elementCount
					};
					elements.push_back(thisElement);
				}
				else if (element == "symbol" || element == "SYMBOL")
				{
					Element thisElement = {
						PW_ELEMENT_TYPE::SYMBOL,
						std::string(),
						CASE_TYPE::NA,
						elementCount
					};
					elements.push_back(thisElement);
				}
				else if (element == "word1")
				{
					Element thisElement = {
						PW_ELEMENT_TYPE::WORD1,
						std::string(),
						CASE_TYPE::LOWER,
						elementCount
					};
					elements.push_back(thisElement);
				}
				else if (element == "Word1")
				{
					Element thisElement = {
						PW_ELEMENT_TYPE::WORD1,
						std::string(),
						CASE_TYPE::PROPER,
						elementCount
					};
					elements.push_back(thisElement);
				}
				else if (element == "WORD1")
				{
					Element thisElement = {
						PW_ELEMENT_TYPE::WORD1,
						std::string(),
						CASE_TYPE::UPPER,
						elementCount
					};
					elements.push_back(thisElement);
				}
				else if (element == "word2")
				{
					Element thisElement = {
						PW_ELEMENT_TYPE::WORD2,
						std::string(),
						CASE_TYPE::LOWER,
						elementCount
					};
					elements.push_back(thisElement);
				}
				else if (element == "Word2")
				{
					Element thisElement = {
						PW_ELEMENT_TYPE::WORD2,
						std::string(),
						CASE_TYPE::PROPER,
						elementCount
					};
					elements.push_back(thisElement);
				}
				else if (element == "WORD2")
				{
					Element thisElement = {
						PW_ELEMENT_TYPE::WORD2,
						std::string(),
						CASE_TYPE::UPPER,
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
								CASE_TYPE::NA,
								elementCount
							};
							elements.push_back(thisElement);
						}
						else if (::isdigit(element.c_str()[0]))
						{
							Element thisElement = {
								PW_ELEMENT_TYPE::NUMERIC,
								element,
								CASE_TYPE::NA,
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
				CASE_TYPE::NA,
				1
			};
			elements.push_back(thisElement);
			break;
		}
	}

	for (uint32_t i = 0; i < count; i++)
	{
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
					std::cout << (char)((element.casetype == CASE_TYPE::UPPER) ? vowels[rand() % sizeof(vowels)] - 32 : vowels[rand() % sizeof(vowels)]);
				break;
			}
			case PW_ELEMENT_TYPE::CONSONANT:
			{
				char consonants[]{ 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z' };

				for (uint32_t i = 0; i < element.count; i++)
					std::cout << (char)((element.casetype == CASE_TYPE::UPPER) ? consonants[rand() % sizeof(consonants)] - 32 : consonants[rand() % sizeof(consonants)]);
				break;
			}
			case PW_ELEMENT_TYPE::SYMBOL:
			{
				for (uint32_t i = 0; i < element.count; i++)
					std::cout << jsonSymbols[rand() % jsonSymbols.size()];
				break;
			}
			case PW_ELEMENT_TYPE::LITERIAL:
			{
				for (uint32_t i = 0; i < element.count; i++)
					std::cout << element.value;
				break;
			}
			case PW_ELEMENT_TYPE::WORD1:
			{
				for (uint32_t i = 0; i < element.count; i++)
				{
					std::string word;
					switch (element.casetype)
					{
					case CASE_TYPE::LOWER:
						word = jsonFirst[rand() % jsonFirst.size()];
						break;
					case CASE_TYPE::UPPER:
						word = toUpper(jsonFirst[rand() % jsonFirst.size()]);
						break;
					case CASE_TYPE::PROPER:
						word = toProper(jsonFirst[rand() % jsonFirst.size()]);
						break;
					default:
						word = jsonFirst[rand() % jsonFirst.size()];
						break;
					}
					std::cout << word;
				}
				break;
			}
			case PW_ELEMENT_TYPE::WORD2:
			{
				for (uint32_t i = 0; i < element.count; i++)
				{
					std::string word;
					switch (element.casetype)
					{
					case CASE_TYPE::LOWER:
						word = jsonSecond[rand() % jsonSecond.size()];
						break;
					case CASE_TYPE::UPPER:
						word = toUpper(jsonSecond[rand() % jsonSecond.size()]);
						break;
					case CASE_TYPE::PROPER:
						word = toProper(jsonSecond[rand() % jsonSecond.size()]);
						break;
					default:
						word = jsonSecond[rand() % jsonSecond.size()];
						break;
					}
					std::cout << word;
				}
				break;
			}
			default:
			{
				for (uint32_t i = 0; i < element.count; i++)
					std::cout << "?";
				break;
			}
			}
		}
		std::cout << std::endl;
	}
}