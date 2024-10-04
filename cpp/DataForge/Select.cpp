#include "Select.h"

Select::Select(Database* d, std::string name, std::vector <std::string> cols, Filter* fil) : Statement(d, name) {
	if (!this->table)
		throw TableNotExist("Table with a given name does not exist in this database");

	if (cols[0] != "*")
		this->columns.assign(cols.begin(), cols.end());
	else {
		auto cs = this->table->getColumns();
		this->columns.assign(cs.begin(), cs.end());
	}

	this->filter = fil;
}

std::string Select::execute() const {
	for (auto col : this->columns)
		if (!this->table->checkColumnExist(col))
			throw ColumnDoesNotExits("Column with a name " + col + " does not exist in a table " + this->table->getName());

	std::string result = "";
	if (!this->filter) {
		result = this->table->toString(this->columns);
	}
	else {
		std::vector <int> indexes;
		result += "|";
		for (auto col : this->columns) {
			result += col;
			result += "\t\t\t|";
			auto cs = this->table->getColumns();
			auto it = std::find(cs.begin(), cs.end(), col);
			indexes.push_back(std::distance(cs.begin(), it));
		}

		result += "\n";
		for (auto record : this->table->getRecords()) {
			if (this->filter->test(record, AND)) {
				result += record->toString(indexes);
				result += "\n";
			}
		}
	}

	return result;
}