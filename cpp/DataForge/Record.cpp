#include "Record.h"
#include <sstream>
#include <iomanip>

void Record::add_value(TYPE type, std::string value) {
	Data* data = Data::createData(type, value);
	this->values.push_back(data);
}

std::string Record::toString() const {
	std::ostringstream result;

	for (auto it : this->values) {
		result << std::setw(10) << it->getData();
	}

	return result.str();
}

std::string Record::toString(std::vector <int> columns) const {
	std::string result = "";

	result += "|";
	for (auto index : columns) {
		result += this->values[index]->getData();
		result += "\t\t\t|";
	}

	return result;
}

Record::~Record() {
	for (auto it : this->values)
		delete it;
}