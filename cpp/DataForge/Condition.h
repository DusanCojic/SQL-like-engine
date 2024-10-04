#ifndef CONDITION_H
#define CONDITION_H

#include <iostream>
#include "Database.h"
#include "Record.h"
#include <algorithm>

class Condition
{
protected:
	int columnIndex;
	Data* value;

public:
	Condition(Database*, std::string, std::string, Data*);
	virtual bool isSatisfied(Record*) const = 0;
};

#endif