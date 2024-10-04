#ifndef DATA_H
#define DATA_H

#include <iostream>

enum TYPE {STRING};

class Data
{
public:
	static Data* createData(TYPE, std::string);
	virtual std::string getData() const = 0;
	virtual TYPE getType() const = 0;
	virtual int compare(Data*) const = 0;
};

#endif