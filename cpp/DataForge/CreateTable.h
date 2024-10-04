#ifndef CREATETABLE_H
#define CREATETABLE_H

#include <iostream>
#include <vector>
#include "Statement.h"
#include <regex>

class CreateTable : public Statement
{
private:
	Database* database;
	std::string tableName;
	std::vector <std::string> cols;

public:
	CreateTable(Database*, std::string, std::vector <std::string>);
	std::string execute() const override;

};

#endif