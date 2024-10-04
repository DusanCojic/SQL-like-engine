#ifndef STRINGDATA_H
#define STRINGDATA_H

#include <iostream>
#include "Data.h"

class StringData : public Data
{
private:
	std::string value;

public:
	StringData(std::string val) : value(val) {}
	std::string getData() const override;
	TYPE getType() const override;
	int compare(Data*) const override;
};

#endif