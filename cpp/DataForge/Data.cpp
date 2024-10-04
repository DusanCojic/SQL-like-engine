#include "Data.h"
#include "StringData.h"
#include "Exceptions.h"

Data* Data::createData(TYPE type, std::string value) {
	if (type == STRING) {
		StringData* data = new StringData(value);
		return data;
	}
	else {
		throw TypeNotSupported("Type is not supported");
	}
}