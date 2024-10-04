#include "Statement.h"
#include "Exceptions.h"

Statement::Statement(Database* d, std::string name) {
	this->table = d->getTable(name);
}