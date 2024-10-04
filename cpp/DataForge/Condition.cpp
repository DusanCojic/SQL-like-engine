#include "Condition.h"

Condition::Condition(Database* d, std::string table, std::string col, Data* val) {
	if (!d->getTable(table))
		throw TableNotExist("Table with a name " + table + " does not exist in this database");

	auto cols = d->getTable(table)->getColumns();
	auto it = std::find(cols.begin(), cols.end(), col);
	if (it == cols.end())
		throw ColumnDoesNotExits("Column with name " + col + " entered in WHERE part does not exist in table " + table);

	this->columnIndex = std::distance(cols.begin(), it);
	this->value = val;
}