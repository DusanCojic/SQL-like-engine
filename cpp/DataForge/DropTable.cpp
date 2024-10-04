#include "DropTable.h"

std::string DropTable::execute() const {
	database->remove_table(this->name);
	return "";
}