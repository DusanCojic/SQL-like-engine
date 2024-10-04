#ifndef FORMAT_H
#define FORMAT_H

#include <iostream>
#include "Database.h"

class Format
{
protected:
	Database* database;
public:
	Format(Database* d) : database(d) {}
	virtual void export_db(std::string) const = 0;
	virtual Database * import(std::string) = 0;
};

#endif