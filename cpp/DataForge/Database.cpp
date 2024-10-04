#include "Database.h"

void Database::add_table(Table* table) {
	if (this->check_table_exists(table->getName()))
		throw TableAlreadyExists("Table with a name " + table->getName() + " already exists in this database");
	this->tables[table->getName()] = table;
}

void Database::remove_table(std::string table) {
	if (!this->check_table_exists(table))
		throw TableNotExist("Table with a name " + table + " does not exit in this database");
	this->tables.erase(table);
}

bool Database::check_table_exists(std::string table) const {
	return this->tables.find(table) != this->tables.end();
}

std::string Database::getTablesDesc() const {
	if (this->tables.size() == 0)
		return "Database contains no tables";

	std::string result = "";

	for (auto it : this->tables) {
		result += "-> ";
		result += it.second->getName();
		result += "(";
		for (auto col : it.second->getColumns())
			result += col + ", ";
		result.erase(result.size() - 2);
		result += ")\n";
	}

	return result;
}

std::vector <Table*> Database::getTables() const {
	std::vector <Table*> t;
	for (auto const& tab : this->tables) {
		t.push_back(tab.second);
	}

	return t;
}

Table* Database::getTable(std::string name) const {
	auto it = this->tables.find(name);
	if (it != this->tables.end())
		return it->second;
	else
		return nullptr;
}

Database::~Database() {
	for (auto it : this->tables)
		delete it.second;
}