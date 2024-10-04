#include "StringData.h"

std::string StringData::getData() const {
	return this->value;
}

TYPE StringData::getType() const {
	return STRING;
}

int StringData::compare(Data* data) const {
	if (StringData* d = dynamic_cast<StringData*>(data)) {
		return this->value.compare(d->getData());
	}

	return 0;
}