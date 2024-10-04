#include <iostream>
#include "Database.h"
#include "Parser.h"
#include <string>
#include <cstdlib>
#include "SQLFormat.h"
#include "CustomFormat.h"
#include <limits>

int main()
{
	Database* d = nullptr;
	Parser* p = nullptr;

	bool created = false;

	// Handle import or create database
	while (!created) {
		std::cout << "> 1) Import database" << std::endl << "> 2) Create database" << std::endl;
		int option;
		std::cin >> option;
		if (option == 1) {
			// Import from custom format
			CustomFormat* cf = new CustomFormat(nullptr);
			std::cout << "Enter a file name: ";
			std::string filename;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::getline(std::cin, filename);
			d = cf->import(filename);
			created = true;
		}
		else if (option == 2) {
			// Create new database
			std::string name;
			std::cout << "> Enter a database name: ";
			std::getline(std::cin, name);
			d = new Database(name);
			created = true;
		}
		else {
			std::cout << "Option entered is invalid. Try again!" << std::endl;
		}
	}

	p = new Parser(d);

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::string query;
	while (true) {
		try {
			std::cout << "> ";
			// Input query
			std::getline(std::cin, query);

			if (query.compare("exit") == 0)
				break;

			if (query.compare("clear") == 0) {
				#ifdef _WIN32
					system("cls");
				#endif
				
				continue;
			}

			if (query.compare("export sql") == 0) {
				// Export in sql format
				SQLFormat* f = new SQLFormat(d);
				std::cout << "Enter a file name: ";
				std::string filename;
				std::getline(std::cin, filename);
				f->export_db(filename);
				continue;
			}

			if (query.compare("export custom") == 0) {
				// Export in custom format
				std::cout << "Enter a file name: ";
				std::string filename;
				std::getline(std::cin, filename);
				CustomFormat* cf = new CustomFormat(d);
				cf->export_db(filename);
				continue;
			}

			// Pass query to parser
			Statement* s = p->parse(query);
			// Execute query
			s->execute();
			delete s;
		}
		catch (const std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}

	delete d;
	delete p;

	return 0;
}