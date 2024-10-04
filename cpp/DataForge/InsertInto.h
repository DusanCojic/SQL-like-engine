#ifndef INSERTINTO_H
#define INSERTINTO_H

#include <iostream>
#include "Statement.h"
#include <vector>

class InsertInto : public Statement
{
private:
	std::vector <std::string> columns;
	std::vector <std::vector <std::string>> values;

public:
	InsertInto(Database*, std::string, std::vector <std::vector <std::string>>, std::vector <std::string>);
	std::string execute() const override;
};

#endif