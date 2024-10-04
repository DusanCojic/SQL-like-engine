#include "Parser.h"
#include "CreateTable.h"
#include "DropTable.h"
#include "ShowTables.h"
#include "InsertInto.h"
#include "Select.h"
#include "Delete.h"
#include "Update.h"
#include "Filter.h"
#include <regex>
#include <string>
#include <sstream>
#include <vector>

std::string toLower(std::string str) {
	std::string result = "";
	for (char c : str)
		result += std::tolower(c);
	return result;
}

Statement* Parser::parse(std::string query) const {
	std::regex createTable(this->createTablePattern, std::regex_constants::icase);
	std::smatch matches;

	// CREATE TABLE
	if (std::regex_search(query, matches, createTable)) {
		std::vector <std::string> columns;
		std::stringstream ss(matches[2]);
		std::string token;

		// Get column names
		while (std::getline(ss, token, ','))
			columns.push_back(token);

		CreateTable* ct = new CreateTable(this->database, matches[1], columns);
		return ct;
	}
	
	// DROP TABLE
	std::regex dropTable(this->dropTablePattern, std::regex_constants::icase);
	if (std::regex_search(query, matches, dropTable)) {
		DropTable* dt = new DropTable(this->database, matches[1]);
		return dt;
	}

	// SHOW TABLES
	std::regex showTables(this->showTablesPattern, std::regex_constants::icase);
	if (std::regex_search(query, matches, showTables)) {
		ShowTables* st = new ShowTables(this->database);
		return st;
	}

	// INSERT INTO
	std::regex insertinto(this->insertIntoPattern, std::regex_constants::icase);
	if (std::regex_search(query, matches, insertinto)) {
		std::vector <std::string> cols;
		std::stringstream ss(matches[2]);
		std::string token;

		// Get column names
		while (std::getline(ss, token, ','))
			cols.push_back(token);

		std::vector <std::vector <std::string>> vals;
		std::vector <std::string> temp_vals;
		
		// Prepare all values for inserting
		std::string substring;
		for (char c : (std::string)matches[3]) {
			if (c == '(')
				substring.clear();

			if (c != '(' && c != ')')
				substring += c;

			if (c == ')')
				temp_vals.push_back(substring);
		}
		
		for (auto str : temp_vals) {
			std::vector <std::string> v;

			std::stringstream ss1(str);
			while (std::getline(ss1, token, ','))
				v.push_back(token);

			vals.push_back(v);
		}

		InsertInto* ii = new InsertInto(this->database, matches[1], vals, cols);
		return ii;
	}


	// SELECT * FROM
	std::regex select(this->selectPattern, std::regex_constants::icase);
	if (std::regex_search(query, matches, select)) {
		std::stringstream ss(matches[1]);
		std::string token;

		// Selector
		std::vector <std::string> cols;
		while (std::getline(ss, token, ','))
			cols.push_back(token);

		Filter* filter;
		if (matches[5].compare("") == 0)
			// If there is no filter
			filter = nullptr;
		else
			// If there is WHERE in query
			filter = new Filter(this->database, matches[4], matches[6]);

		Select* s = new Select(this->database, matches[4], cols, filter);
		return s;
	}

	// DELETE FROM
	std::regex deletee(this->deletePattern, std::regex_constants::icase);
	if (std::regex_search(query, matches, deletee)) {
		Filter* filter = new Filter(this->database, matches[1], matches[2]);

		Delete* d = new Delete(this->database, matches[1], filter);
		return d;
	}

	// UPDATE ... SET
	std::regex update(this->updatePattern, std::regex_constants::icase);
	if (std::regex_search(query, matches, update)) {
		std::vector <std::string> tokens;
		std::stringstream ss(matches[2]);
		std::string token;

		// Get changes
		while (std::getline(ss, token, ','))
			tokens.push_back(token);

		std::vector <std::pair<std::string, std::string>> changes;

		for (auto t : tokens) {
			std::stringstream ss1(t);
			int first = 1;
			std::pair <std::string, std::string> p;
			while (std::getline(ss1, token, '=')) {
				if (first) {
					p.first = token;
					first = 0;
				}
				else {
					size_t end = token.find_last_not_of(" ");
					if (end != std::string::npos)
						token.erase(end + 1);
					p.second = token;
				}
			}
			changes.push_back(p);
		}

		// Prepare filter
		Filter* filter = new Filter(this->database, matches[1], matches[3]);

		Update* u = new Update(this->database, matches[1], changes, filter);
		return u;
	}

	// SYNTAX ERRORS

	// CREATE TABLE syntax error
	std::regex ctt(R"((\b(?:[CREATE]+)\b)\s+(\b(?:[TABLE]+)\b)\s*(\w*)\s*(?:\([^)]+\))*)", std::regex_constants::icase);
	if (std::regex_search(query, matches, ctt)) {
		if (toLower(matches[1]).compare("create") != 0)
			throw SyntaxError("Word CREATE is misspelled!");
		if (toLower(matches[2]).compare("table") != 0)
			throw SyntaxError("Word TABLE is misspelled!");
		if (matches[3].compare("") == 0)
			throw SyntaxError("Table name is missing");
		if (matches[4].compare("") == 0)
			throw SyntaxError("Missing column definitions!");
	}

	// DROP TABLE syntax error
	std::regex dp(R"((\b(?:[DROP]+){3}\b)\s+(\b(?:[TABLE]+){3}\b)\s*(\w*))", std::regex_constants::icase);
	if (std::regex_search(query, matches, dp)) {
		if (toLower(matches[1]).compare("drop") != 0)
			throw SyntaxError("Word DROP is misspelled!");
		if (toLower(matches[2]).compare("table") != 0)
			throw SyntaxError("Word TABLE is misspelled!");
		if (matches[3].compare("") == 0)
			throw SyntaxError("Table name is missing");
	}

	// SHOW TABLES syntax error
	std::regex stt(R"((\b(?:[SHOW]+)\b)\s+(\b(?:[TABLE]+)\b))", std::regex_constants::icase);
	if (std::regex_search(query, matches, stt)) {
		if (toLower(matches[1]).compare("show") != 0)
			throw SyntaxError("Word SHOW is misspelled");
		if (toLower(matches[2]).compare("table") != 0)
			throw SyntaxError("Word TABLE is misspelled!");
	}

	// INSERT INTO syntax error
	std::regex ii(R"((\b(?:[INSERT]+)\b)\s+(\b(?:[INTO]+)\b)\s*(\w*)\s*(\([^)]+\))*\s*(\b(?:[VALUES]+)\b)\s*(\([^)]+\))*)", std::regex_constants::icase);
	if (std::regex_search(query, matches, ii)) {
		if (toLower(matches[1]).compare("insert") != 0)
			throw SyntaxError("Word INSERT is misspelled!");
		if (toLower(matches[2]).compare("into") != 0)
			throw SyntaxError("Word INTO is misspelled!");
		if (matches[3].compare("") == 0)
			throw SyntaxError("Table name is missing!");
		if (matches[4].compare("") == 0)
			throw SyntaxError("Missing column definitions!");
		if (toLower(matches[5]).compare("values") != 0)
			throw SyntaxError("Word VALUES is misspelled!");
		if (matches[6].compare("") == 0)
			throw SyntaxError("Values are missing!");
	}

	// SELECT syntax error
	std::regex sel(R"((\b(?:[SELECT]+)\b)\s*((\*)|([^,]+(?:,[^,]+)*))\s*(\b(?:[FROM]+)\b)\s*(\w*)\s*(\b(?:[WHERE]+){3}\b)*\s*(.*))", std::regex_constants::icase);
	if (std::regex_search(query, matches, sel)) {
		if (toLower(matches[1]).compare("select") != 0)
			throw SyntaxError("Word SELECT is misspelled!");
		if (toLower(matches[5]).compare("from") != 0)
			throw SyntaxError("Word FROM is misspelled!");
		if (matches[3].compare("") == 0)
			throw SyntaxError("Missing selector!");
		if (matches[7].compare("") != 0)
			throw SyntaxError("Missing condition!");
	}

	std::regex dd(R"((\b(?:[DELETE]+)\b)\s*(\b(?:[FROM]+)\b)\s*(\w*)\s*(\b(?:[WHERE]+)\b)+\s*(.*))", std::regex_constants::icase);
	if (std::regex_search(query, matches, dd)) {
		if (toLower(matches[1]).compare("delete") != 0)
			throw SyntaxError("Word DELETE is misspelled!");
		if (toLower(matches[2]).compare("from") != 0)
			throw SyntaxError("Word FROM is misspelled!");
		if (matches[3].compare("") == 0)
			throw SyntaxError("Table name is missing!");
		if (toLower(matches[4]).compare("where") != 0)
			throw SyntaxError("Word WHERE is misspelled!");
		if (matches[5].compare("") == 0)
			throw SyntaxError("Condition is missing!");
	}

	std::regex up(R"((\b(?:[UPDATE]+)\b)\s*(\w*)\s*(\b(?:[SET]+)\b)\s*([^,]+(?:,[^,]+)*)\s*(\b(?:[WHERE]+)\b)+\s*(.*))", std::regex_constants::icase);
	if (std::regex_search(query, matches, up)) {;
		if (toLower(matches[1]).compare("update") != 0)
			throw SyntaxError("Word UPDATE is misspelled!");
		if (toLower(matches[3]).compare("set") != 0)
			throw SyntaxError("Word SET is misspelled!");
		if (matches[2].compare("") == 0)
			throw SyntaxError("Table name is missing!");
		if (matches[4].compare(" ") == 0)
			throw SyntaxError("Values missing!");
		if (matches[5].compare("where") != 0)
			throw SyntaxError("Word WHERE is misspelled!");
		if (matches[6].compare("") == 0)
			throw SyntaxError("Condition is missing!");
	}

	throw SyntaxError("Invalid query");

	return nullptr;
}