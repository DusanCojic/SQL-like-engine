#ifndef CUSTOMFORMAT_H
#define CUSTOMFORMAT_H

#include "Format.h"

class CustomFormat : public Format
{
public:
	CustomFormat(Database* d) : Format(d) {}
	void export_db(std::string) const override;
	Database* import(std::string) override;
};

#endif