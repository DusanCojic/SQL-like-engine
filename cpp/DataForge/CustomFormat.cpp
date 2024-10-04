#include "CustomFormat.h"
#include <fstream>
#include "Exceptions.h"
#include <string>
#include <sstream>
#include "Table.h"

void CustomFormat::export_db(std::string filename) const {
	std::ofstream output(filename);

	if (!this->database)
		throw DatabaseNotExist("Database that you want to export does not exist!");

	auto tables = this->database->getTables();

	std::string str = "";
	str += this->database->getName();
	str += "\n";
	str += std::to_string(tables.size()) + "\n";
	for (auto table : tables) {
		str += table->getName() + "\n";
		int n = table->getColumns().size();
		str += std::to_string(n);
		str += "\n";
		for (auto c : table->getColumns())
			str += c + "\n";
		auto recs = table->getRecords();
		n = table->getRecords().size();
		str += std::to_string(n);
		str += "\n";
		for (auto r : recs) {
			auto vals = r->getValues();
			for (auto v : vals)
				str += v->getData() + ",";
			str.erase(str.size() - 1);
			str += "\n";
		}
	}

	str.erase(str.size() - 1);
	output << str;

	output.close();
}

Database* CustomFormat::import(std::string filename) {
	std::ifstream input(filename);

	std::string databaseName;
	std::getline(input, databaseName);

	Database* db = new Database(databaseName);

	std::string temp;
	std::getline(input, temp);
	int numOfTables = std::stoi(temp);

	for (int i = 0; i < numOfTables; i++) {
		std::string tableName;
		std::getline(input, tableName);
		
		std::getline(input, temp);
		int numOfCols = std::stoi(temp);

		std::vector <std::string> cols;
		for (int j = 0; j < numOfCols; j++) {
			std::getline(input, temp);
			cols.push_back(temp);
		}

		Table* table = new Table(tableName, cols);

		std::getline(input, temp);
		int numOfRecs = std::stoi(temp);
		for (int j = 0; j < numOfRecs; j++) {
			Record* rec = new Record();

			std::getline(input, temp);
			
			std::stringstream ss(temp);
			std::string token;
			while (std::getline(ss, token, ','))
				rec->add_value(STRING, token);
			
			table->add_record(rec);
		}

		db->add_table(table);
	}

	input.close();

	return db;
}