#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include "Record.h"
#include <algorithm>

class Table
{
private:
	std::string name;
	std::vector <std::string> columns;
	std::vector <Record*> records;

public:
	Table(std::string, std::vector <std::string>);
	void add_record(Record*);
	void remove_record(Record*);

	std::string getName() const { return this->name; }
	std::vector <std::string> getColumns() const { return this->columns; }
	bool checkColumnExist(std::string) const;
	std::vector <Record*> getRecords() const { return this->records; }
	int getColumnIndex(std::string) const;

	std::string toString() const;
	std::string toString(std::vector <std::string>) const;

	~Table();
};

#endif