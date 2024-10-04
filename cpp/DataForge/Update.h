#ifndef UPDATE_H
#define UPDATE_H

#include "Statement.h"
#include "Filter.h"

class Update : public Statement
{
private:
	std::vector <std::pair<std::string, std::string>> changes;
	Filter* filter;

public:
	Update(Database*, std::string, std::vector <std::pair<std::string, std::string>>, Filter*);
	std::string execute() const override;
};

#endif