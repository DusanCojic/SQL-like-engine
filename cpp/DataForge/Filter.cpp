#include "Filter.h"
#include "Condition.h"
#include "Equal.h"
#include "Greater.h"
#include "Lesser.h"
#include <sstream>

Filter::Filter(Database* database, std::string table, std::string conds) {
	std::vector<std::string> tokens;
	std::size_t pos = 0, lastPos = 0;

	std::string token;
	std::string str = conds;
	std::string delimiter;
	if (str.find(AND) != std::string::npos)
		delimiter = " AND ";
	else
		delimiter = " and ";
	while ((pos = str.find(delimiter, lastPos)) != std::string::npos) {
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		lastPos = pos + delimiter.length();
	}
	tokens.push_back(str.substr(lastPos));

	for (auto t : tokens) {
		char delimiter;
		if (t.find("=") != std::string::npos)
			delimiter = '=';
		else if (t.find(">") != std::string::npos)
			delimiter = '>';
		else if (t.find("<") != std::string::npos)
			delimiter = '<';

		std::vector <std::string> temp;
		std::stringstream ss1(t);
		while (std::getline(ss1, token, delimiter))
			temp.push_back(token);

		Condition* con = nullptr;
		if (delimiter == '=')
			con = new Equal(database, table, temp[0], Data::createData(STRING, temp[1]));
		else if (delimiter == '>')
			con = new Greater(database, table, temp[0], Data::createData(STRING, temp[1]));
		else if (delimiter == '<')
			con = new Lesser(database, table, temp[0], Data::createData(STRING, temp[1]));

		this->add_condition(con);
	}
}

bool Filter::test(Record* record, LOGICAL_OPERATOR lo) const {
	if (lo == AND) {
		for (auto cond : this->conditions) {
			if (!cond->isSatisfied(record))
				return false;
		}

		return true;
	}

	return false;
}

Filter::~Filter() {
	for (auto cond : this->conditions)
		delete cond;
}