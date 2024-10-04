#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <unordered_map>
#include "Table.h"

enum FORMAT {CUSTOM, SQL};

class Database
{
private:
	std::string name;
	std::unordered_map <std::string, Table*> tables;

public:
	Database(std::string name) : name(name) {}
	void add_table(Table*);
	void remove_table(std::string);
	bool check_table_exists(std::string) const;

	std::string getName() const { return this->name; }
	std::string getTablesDesc() const;
	std::vector <Table*> getTables() const;
	Table* getTable(std::string) const;

	~Database();
};

#endif