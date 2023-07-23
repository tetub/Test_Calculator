#pragma once
#include "Header.h"
#include <vector>
class Calculator{
private:
	std::map<std::string, double> variable;
	std::map<std::string, std::string> function;
	bool isExistAll(std::string identidier);
	bool isExistVariable(std::string identidier);
	bool isExistFunction(std::string identidier);
	void setVariable(std::string identidify, double value);
	void setFunction(std::string identidify, std::string value);
	std::string func(std::string identify);
	double funci(std::string identify_1, std::string simbol, std::string identify_2);
	std::string getAny(std::string identidify);
	void var(std::string identify);
	auto let(std::string  identify_1, double variable);
	auto let(std::string identify_1, std::string identify_2);
	auto fn(std::string identify_1, std::string identify_2);
	auto fn(std::string identify_1, std::string identify_2, std::string operation, std::string identify_3);
	void print(std::string identify_1);
	auto printvars();
	auto printfns();
	std::vector<std::string> separator(std::string text);
	std::string input();
	int switcher(std::vector<std::string>);
public:
	void handler();
	Calculator() = default;
};