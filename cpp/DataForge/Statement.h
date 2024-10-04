#ifndef STATEMENT_H
#define STATEMENT_H

#include "Database.h"

class Statement
{
protected:
	Table* table;
public:
	Statement(Database*, std::string);
	virtual std::string execute() const = 0;
};

#endif