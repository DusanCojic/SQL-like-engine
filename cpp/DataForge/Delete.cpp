#include "Delete.h"
#include <string>

Delete::Delete(Database* d, std::string name, Filter* f) : Statement(d, name), filter(f) {}

std::string Delete::execute() const {
	if (!this->table)
		throw TableNotExist("Table with a given name does not exist in this database");

	auto recs = this->table->getRecords();

	int count = 0;
	for (auto r : recs) {
		if (this->filter->test(r, AND)) {
			this->table->remove_record(r);
			count++;
		}
	}

	std::string res = "Number of rows affected: " + std::to_string(count);
	return res;
}