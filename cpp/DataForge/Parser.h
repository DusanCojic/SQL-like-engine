#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include "Exceptions.h"
#include "Statement.h"

class Parser
{
private:
	const std::string createTablePattern = R"(CREATE\s+TABLE\s+(\w+)\s*\(([^,]+(?:,[^, ]+)*)\)$)";
	const std::string dropTablePattern = R"(DROP\s+TABLE\s+(\w+))";
	const std::string showTablesPattern = R"(SHOW\s+TABLES)";
	const std::string insertIntoPattern = R"(INSERT\s+INTO\s+(\w+)\s+\(([^,]+(?:,[^,]+)*)\)\s+VALUES\s((\([^,]+(?:,[^,]+)*\))+)$)";
	const std::string selectPattern = R"(SELECT\s+((\*)|([^,]+(?:,[^,]+)*))\s+FROM\s+(\w+)\s*(?:(WHERE)\s+((?:[^,]+(?:\s*[><=]\s*[^,]+)*(?:\s+AND\s+[^,]+)*)*)\s*)?$)";
	const std::string deletePattern = R"(DELETE\s+FROM\s+(\w+)\s+WHERE\s+((?:[^,]+(?:\s*[><=]\s*[^,]+)*(?:\s+AND\s+[^,]+)*)*)\s*)";
	const std::string updatePattern = R"(UPDATE\s+(\w+)\s+SET\s+([^,]+(?:,[^,]+)*\s+)WHERE\s+((?:[^,]+(?:\s*[><=]\s*[^,]+)*(?:\s+AND\s+[^,]+)*)*)\s*)";

	Database* database;

public:
	Parser(Database* d) : database(d) {}
	Statement* parse(std::string) const;
};

#endif