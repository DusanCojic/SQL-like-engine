#include "SQLFormat.h"
#include "Exceptions.h"
#include <fstream>
#include <sstream>
#include "Parser.h"

void SQLFormat::export_db(std::string filename) const {
	if (!this->database)
		throw DatabaseNotExist("Database that you want to export does not exist!");
	
	std::ofstream output(filename);

	auto tables = this->database->getTables();
	for (auto table : tables) {
		std::string query = "CREATE TABLE ";
		query += table->getName();
		std::string cols = " (\n";
		bool primary = false;
		for (auto c : table->getColumns()) {
			cols += "\t" + c + " VARCHAR(40)";
			if (!primary) {
				cols += " PRIMARY KEY";
				primary = true;
			}
			cols += ",\n";
		}
		cols.erase(cols.size() - 2);
		cols += "\n);";

		query += cols;

		output << query << std::endl;

		auto recs = table->getRecords();
		if (recs.size() == 0)
			continue;

		cols.clear();
		cols = "(";
		for (auto c : table->getColumns())
			cols += c + ",";
		cols.erase(cols.size() - 1);
		cols += ")";
		std::string q = "INSERT INTO " + table->getName() + " " + cols + " VALUES ";
		for (auto r : recs) {
			q += "(";
			auto vals = r->getValues();
			for (auto v : vals)
				q += "\"" + v->getData() + "\"" + ",";
			q.erase(q.size() - 1);
			q += "),";
		}

		q.erase(q.size() - 1);
		q += ";";
		output << q << std::endl;
	}

	output.close();
}

Database * SQLFormat::import(std::string filename) {
	return nullptr;
}