#ifndef SHOWTABLES_H
#define SHOWTABLES_H

#include "Statement.h"
#include "Database.h"

class ShowTables : public Statement
{
private:
	Database* database;

public:
	ShowTables(Database* d) : Statement(d, ""), database(d) {}
	std::string execute() const override { return this->database->getTablesDesc(); }
};

#endif