#include "CreateTable.h"
#include <string>
#include <sstream>
#include "Exceptions.h"

CreateTable::CreateTable(Database* d, std::string name, std::vector <std::string> columns) : Statement(d, name) {
	this->database = d;
	this->tableName = name;
	this->cols.assign(columns.begin(), columns.end());
}

std::string CreateTable::execute() const {
	for (auto it : this->cols)
		if (std::count(this->cols.begin(), this->cols.end(), it) > 1)
			throw ColumnsWithSameName("Column with name " + it + " appears multiple times");

	Table* table = new Table(this->tableName, this->cols);
	database->add_table(table);
	return "";
}