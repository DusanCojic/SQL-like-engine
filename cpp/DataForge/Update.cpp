#include "Update.h"
#include <string>

Update::Update(Database* d, std::string name, std::vector <std::pair <std::string, std::string>> cgs, Filter* f) : Statement(d, name) {
	this->changes.assign(cgs.begin(), cgs.end());
	this->filter = f;
}

std::string Update::execute() const {
	if (!this->table)
		throw TableNotExist("Table with a given name does not exist in this database");

	for (auto c : this->changes)
		if (!this->table->checkColumnExist(c.first))
			throw ColumnDoesNotExits("Column with a name " + c.first + " does not exist in the table " + this->table->getName());

	int count = 0;
	for (auto rec : this->table->getRecords()) {
		if (this->filter->test(rec, AND)) {
			count++;
			for (auto c : this->changes)
				rec->set_value(this->table->getColumnIndex(c.first), Data::createData(STRING, c.second));
		}
	}

	std::string res = "Number of rows affected: "  + std::to_string(count);
	return res;
}