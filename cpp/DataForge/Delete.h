#ifndef DELETE_H
#define DELETE_H

#include "Statement.h"
#include "Filter.h"

class Delete : public Statement
{
private:
	Filter* filter;

public:
	Delete(Database*, std::string, Filter*);
	std::string execute() const override;
};

#endif