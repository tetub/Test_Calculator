#include "Calculator.h"
#include <vector>
#include <algorithm>
#include <cassert>
#include <iomanip>

bool isAlphaNumericUnderscore(const std::string& str) 
{
	for	(char c : str) 
	{
		if (!std::isalnum(c) && c != '_') 
		{
			return false;
		}
	}
	return true;
}

bool correctIdentify(const std::string& word) {
	if (isAlphaNumericUnderscore(word)  && !std::isdigit(word[0])){
		return true;
	}
	else {
		return false;
	}
}

void testIscorrectIdentify() { //tester
	assert(correctIdentify("abcde") == true);
	assert(correctIdentify("_abcde") == true);
	assert(correctIdentify("AbcDe") == true);
	assert(correctIdentify("1AbcDe") == false);
}

bool isNumeric(std::string str)
{
	if (std::isdigit(str[0]))
		return true;
	else
		return false;
}

bool isSimbol(std::string word, std::string simbol)
{
	if (word == simbol)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Calculator::isExistAll(std::string identidier)
{
	auto findvariable = variable.find(identidier);
	auto findfunction = function.find(identidier);
	if (findvariable != variable.end())
	{
		return true;
	}
	else
	{
		if (findfunction != function.end())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

void Calculator::setVariable(std::string identidify, double value)
{
	variable[identidify] = value;
}

void Calculator::setFunction(std::string identidify, std::string value)
{
	function[identidify] = value;
}

void Calculator::var(std::string identify) 
{
	if (!isExistAll(identify)) {
		setVariable(identify, NAN);
	}
	else {
		std::cout << "Error: this variable is identify occupied" << std::endl;
	}
}

auto Calculator::let(std::string identify, double variable) 
{
	try {
		setVariable(identify, variable);
	}
	catch (...) {

	}
}

auto Calculator::let(std::string identify_1, std::string identify_2) 
{
	if (Calculator::isExistAll(identify_2) == true)
	{
		setVariable(identify_1, std::stod(getAny(identify_2)));
	}

}

auto Calculator::fn(std::string identify_1, std::string identify_2)
{
	if (Calculator::isExistAll(identify_2) == true)
	{
		setFunction(identify_1, identify_2);
	}
}

auto Calculator::fn(std::string identify_1, std::string identify_2, std::string operation, std::string identify_3)
{
	if (Calculator::isExistAll(identify_2) == true && Calculator::isExistAll(identify_3) == true)
	{
		setFunction(identify_1, identify_2 + operation + identify_3);
	}
}



auto Calculator::printvars()
{
	if (!variable.empty())
	{
		for (auto& pair : variable) 
		{
			std::string identify = pair.first;
			if (variable[identify] == NAN)
			{
				std::cout << identify << std::fixed << std::setprecision(2) << ":" << "nan" << std::endl;
			}
			else
			{
				std::cout << identify << std::fixed << std::setprecision(2) << ":" << std::to_string(variable[identify]) << std::endl;
			}
		}
	}

}

auto Calculator::printfns()
{
	if (variable.size() > 0)
	{
		for (auto& i : function)
		{
			std::string identify = i.first;
			if (function[identify] == "")
			{
				std::cout << "nan" << std::endl;
			}
			else
			{
				std::vector<std::string> words = separator(function[identify]);
				if (words.size() == 1) {
					std::cout << identify <<":" << std::fixed << std::setprecision(2) << (getAny(words[0])) << std::endl;
				}
				if (words.size() == 3) {
					std::cout << identify << ":" << std::fixed << std::setprecision(2) << funci(words[0], words[1], words[2]) << std::endl;
				}
			}
		}
	}
}

std::string Calculator::input() 
{
	std::string text;
	try {
		std::getline(std::cin, text);
	}
	catch (...) {}
	return text;
}

std::vector<std::string> Calculator::separator(std::string text)
{
	std::string delimiters = " =+-*/";
	std::vector<std::string> words;
	std::string word;
	bool add = false;
	for (int i = 0; i < text.size(); i++)
	{
		if (text[i] == delimiters[0] || text[i] == delimiters[1] || text[i] == delimiters[2] || text[i] == delimiters[3] || text[i] == delimiters[4] || text[i] == delimiters[5]) 
		{
			if (text[i] == delimiters[0])
			{
				words.push_back(word);
				word = "";
				words.push_back(" ");
			}
			if (text[i] == delimiters[1])
			{
				words.push_back(word);
				word = "";
				words.push_back("=");
			}
			if (text[i] == delimiters[2])
			{
				words.push_back(word);
				word = "";
				words.push_back("+");
			}
			if (text[i] == delimiters[3])
			{
				words.push_back(word);
				word = "";
				words.push_back("-");
			}
			if (text[i] == delimiters[4])
			{
				words.push_back(word);
				word = "";
				words.push_back("*");
			}
			if (text[i] == delimiters[5])
			{
				words.push_back(word);
				word = "";
				words.push_back("/");
			}
		}
		else {
			word += text[i];
		}
	}
	words.push_back(word);
	return words;
}

std::string Calculator::getAny(std::string identidify) 
{
	std::map<std::string, double >::iterator itvariable = variable.find(identidify);
	if (itvariable != variable.end()) 
	{
		return std::to_string(itvariable->second);
	}
	else {
		std::map<std::string, std::string >::iterator itfuction = function.find(identidify);
		if (itfuction != function.end()) 
		{
			std::vector<std::string> words = separator(itfuction->second);
			if (words.size() == 1) 
			{
				return std::to_string(variable[words[0]]);
			}
			if (words.size() == 3) 
			{
				return std::to_string(funci(words[0], words[1], words[2]));
			}
			return itfuction->second;
		}
	}
}

double Calculator::funci(std::string identify_1, std::string simbol, std::string identify_2)
{
	double answer = NAN;
	if (simbol == "+")
		answer = std::stod(getAny(identify_1)) + std::stod(getAny(identify_2));
	if (simbol == "-")
		answer = std::stod(getAny(identify_1)) - std::stod(getAny(identify_2));
	if (simbol == "*")
		answer = std::stod(getAny(identify_1)) * std::stod(getAny(identify_2));
	if (simbol == "/")
		answer = std::stod(getAny(identify_1)) / std::stod(getAny(identify_2));
	return answer;
}

void Calculator::print(std::string identify)
{

	if (variable.find(identify) != variable.end())
	{
		if (std::isnan(variable[identify]))
		{
			std::cout << "nan" << std::endl;
		}
		else {
			std::cout << std::fixed << std::setprecision(2) << variable[identify] << std::endl;
		}
	}
	if (function.find(identify) != function.end())
	{
		if (function[identify] == "")
		{
			std::cout <<"nan" << std::endl;
		}
		else
		{
			std::vector<std::string> words = separator(function[identify]);
			if (words.size() == 1) {
				std::cout <<  std::fixed << std::setprecision(2) << (getAny(words[0])) << std::endl;
			}
			if (words.size() == 3) {
				std::cout << std::fixed << std::setprecision(2) << funci(words[0], words[1], words[2]) << std::endl;
			}
		}
	}
}

int Calculator::switcher(std::vector<std::string> words)
{
	int answer = 0;
	if (words[0] == "var") {
		answer = 1;
	}
	if (words[0] == "let") {
		answer = 2;
	}
	if (words[0] == "fn") {
		answer = 3;
	}
	if (words[0] == "print") {
		answer = 4;
	}
	if (words[0] == "printvars") {
		answer = 5;
	}
	if (words[0] == "printfns") {
		answer = 6;
	}

	return answer;
}


void Calculator::handler()
{
	std::vector<std::string> words;
	std::string text;
	std::string an;
	int infinity = 0;

	testIscorrectIdentify(); //test (syntax: correct or incorrect name identify)

	while (infinity == 0)
	{
		text = input();
		words = separator(text);
		
		switch (switcher(words))
		{
		case 0:
			break;
		case 1:
			if (words.size() == 3)
				if (correctIdentify(words[2]))
				{

					if (isSimbol(words[1], " "))
					{
						var(words[2]);
					}
				}
				else {
					std::cout << "Error syntax: incorrect name identify" << std::endl;
				}
			break;
		case 2:
			if (words.size() == 5) 
			{
				if (correctIdentify(words[2]))
				{
					if (isSimbol(words[1], " ") && isNumeric(words[4]) && isSimbol(words[3], "=")) 
					{
						let(words[2], std::stod(words[4]));
					}
					else 
					{
						let(words[2], words[4]);
					}
				}
				else
				{
					std::cout << "Error syntax: incorrect name identify" << std::endl;
				}
			}
			break;
		case 3:
			if (words.size() <= 7)
			{
				if (words.size() == 7) {
					if (correctIdentify(words[2]) && correctIdentify(words[4]) && correctIdentify(words[6]))
					{
						fn(words[2], words[4], words[5], words[6]);
					}
					else {
						std::cout << "Error syntax: incorrect name identify" << std::endl;
					}
				}
				if (words.size() == 5)
				{
					if (correctIdentify(words[2]) && correctIdentify(words[4]) && correctIdentify(words[6]))
					{
						fn(words[2], words[4]);
					}
					else {
						std::cout << "Error syntax: incorrect name identify" << std::endl;
					}
				}
			}
			break;
		case 4:
			if(correctIdentify(words[2]))
			{
				print(words[2]);
			}
			else 
			{
				std::cout << "Error syntax: incorrect name identify" << std::endl;
			}
			
			break;
		case 5:
			printvars();
			break;
		case 6:
			printfns();
			break;
		}

	}
}
