#ifndef FILTER_H
#define FILTER_H

#include <iostream>
#include <vector>
#include "Condition.h"
#include "Table.h"
#include "Record.h"

enum LOGICAL_OPERATOR {AND};

class Filter
{
private:
	std::vector <Condition*> conditions;

public:
	Filter(Database*, std::string, std::string);
	void add_condition(Condition* c) { this->conditions.push_back(c); }
	bool test(Record*, LOGICAL_OPERATOR) const;

	~Filter();
};

#endif