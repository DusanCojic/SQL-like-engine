#ifndef SELECT_H
#define SELECT_H

#include <iostream>
#include "Statement.h"
#include "Filter.h"
#include <vector>

class Select : public Statement
{
private:
	std::vector <std::string> columns;
	Filter* filter;

public:
	Select(Database*, std::string, std::vector <std::string>, Filter*);
	std::string execute() const override;
};

#endif