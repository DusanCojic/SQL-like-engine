#ifndef GREATER_H
#define GREATER_H

#include "Condition.h"

class Greater : public Condition
{
public:
	Greater(Database* d, std::string table, std::string col, Data* value) : Condition(d, table, col, value) {}
	bool isSatisfied(Record* record) const override { return record->get_value(this->columnIndex)->compare(this->value) > 0; }
};

#endif