#ifndef DROPTABLE_H
#define DROPTABLE_H

#include <iostream>
#include "Statement.h"

class DropTable : public Statement
{
private:
	Database* database;
	std::string name;

public:
	DropTable(Database* d, std::string name) : Statement(d, name), database(d), name(name) {};
	std::string execute() const override;
};

#endif