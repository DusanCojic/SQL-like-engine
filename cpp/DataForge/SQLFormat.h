#ifndef SQLFORMAT_H
#define SQLFORMAT_H

#include "Format.h"

class SQLFormat : public Format
{
public:
	SQLFormat(Database* d) : Format(d) {}
	void export_db(std::string) const override;
	Database* import(std::string) override;
};

#endif