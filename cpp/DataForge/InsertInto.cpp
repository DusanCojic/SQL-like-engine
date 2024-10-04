#include "InsertInto.h"
#include "Exceptions.h"
#include <string>

InsertInto::InsertInto(Database* d, std::string name, std::vector <std::vector <std::string>> vals, std::vector <std::string> cols) : Statement(d, name) {
	this->columns.assign(cols.begin(), cols.end());
	this->values.assign(vals.begin(), vals.end());
}

std::string InsertInto::execute() const {
	if (!this->table)
		throw TableNotExist("Table with given name does not exit in this database");

	if (this->columns.size() != this->table->getColumns().size())
		throw ColumnsDoNotMatch("Columns do not match");

	for (auto it : values)
		if (table->getColumns().size() != it.size())
			throw ValuesLesserThanColumns("Number of values provided are not equal to the number of columns in the table");

	for (int i = 0; i < this->columns.size(); i++)
		if (this->columns[i].compare(this->table->getColumns()[i]) != 0)
			throw ColumnsDoNotMatch("Columns do not match");

	for (auto it : this->values) {
		Record* r = new Record();
		for (auto it1 : it)
			r->add_value(STRING, it1);
		this->table->add_record(r);
	}

	std::string res = "Number of rows affected: " + std::to_string(this->values.size());
	return res;
}