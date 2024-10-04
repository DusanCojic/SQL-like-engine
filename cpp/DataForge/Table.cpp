#include "Table.h"
#include <sstream>
#include <iomanip>

Table::Table(std::string name, std::vector <std::string> cols) {
	this->name = name;
	this->columns.assign(cols.begin(), cols.end());
}

void Table::add_record(Record* record) {
	this->records.push_back(record);
}

void Table::remove_record(Record* record) {
	auto it = std::find(this->records.begin(), this->records.end(), record);
	this->records.erase(it);
}

std::string Table::toString() const {
	std::ostringstream result;

	for (auto c : this->columns) {
		result << std::setw(10) << c;
	}
	result << std::endl;

	for (int i = 0; i < this->columns.size(); i++)
		result << std::setw(10) << "-------";

	result << std::endl;
	for (auto r : this->records)
		result << r->toString() << std::endl;

	return result.str();
}

bool Table::checkColumnExist(std::string column) const {
	return std::find(this->columns.begin(), this->columns.end(), column) != this->columns.end();
}

int Table::getColumnIndex(std::string name) const {
	auto it = std::find(this->columns.begin(), this->columns.end(), name);
	if (it != this->columns.end())
		return std::distance(this->columns.begin(), it);
	else
		return -1;
}

std::string Table::toString(std::vector <std::string> cols) const {
	std::string result = "";

	std::vector <int> indexes;
	for (auto col : cols) {
		auto it = std::find(this->columns.begin(), this->columns.end(), col);
		indexes.push_back(std::distance(this->columns.begin(), it));
	}

	result += "|";
	for (auto ind : indexes) {
		result += this->columns[ind];
		result += "\t\t\t|";
	}

	result += "\n";

	for (auto row : this->records) {
		result += row->toString(indexes);
		result += "\n";
	}

	return result;
}

Table::~Table() {
	for (auto it : this->records)
		delete it;
}