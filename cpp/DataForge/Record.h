#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <vector>
#include "Data.h"
#include "StringData.h"
#include "Exceptions.h"

class Record
{
private:
	std::vector <Data*> values;

public:
	Record() {}
	void add_value(TYPE, std::string);
	Data* get_value(int index) const { return this->values[index]; }
	void set_value(int index, Data* new_value) { this->values[index] = new_value; }
	std::vector <Data*> getValues() const { return this->values; }

	std::string toString() const;
	std::string toString(std::vector <int>) const;

	~Record();
};

#endif