#pragma once
#include "Header.h"
#include <vector>
class Calculator{
private:
	std::map<std::string, double> all;
	std::map<std::string, double> variable;
	std::map<std::string, std::string> function;

	double getall(std::string identify);
	void setall(std::string identify, double value);
	bool inall(std::string identify, double value);
	bool isExistAll(std::string identify);
	void setVariable(std::string identify, double value);
	void setFunction(std::string identify, std::string value);
	double funci(std::string identify_1, std::string simbol, std::string identify_2, std::string);
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