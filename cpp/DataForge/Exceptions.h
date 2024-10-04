#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>
#include <exception>

class TypeNotSupported : public std::exception {
private:
	std::string message;

public:
	TypeNotSupported(std::string msg) : message(msg) {}

	const char* what() const noexcept override {
		return message.c_str();
	}
};

class TableAlreadyExists : public std::exception {
private:
	std::string message;

public:
	TableAlreadyExists(std::string msg) : message(msg) {}

	const char* what() const noexcept override {
		return message.c_str();
	}
};


class SyntaxError : public std::exception {
private:
	std::string message;

public:
	SyntaxError(std::string msg) : message(msg) {}

	const char* what() const noexcept override {
		return message.c_str();
	}
};

class ColumnsWithSameName : public std::exception {
private:
	std::string message;

public:
	ColumnsWithSameName(std::string msg) : message(msg) {}

	const char* what() const noexcept override {
		return message.c_str();
	}
};

class TableNotExist : public std::exception {
private:
	std::string message;

public:
	TableNotExist(std::string msg) : message(msg) {}

	const char* what() const noexcept override {
		return message.c_str();
	}
};

class ValuesLesserThanColumns : public std::exception {
private:
	std::string message;

public:
	ValuesLesserThanColumns(std::string msg) : message(msg) {}

	const char* what() const noexcept override {
		return message.c_str();
	}
};

class ColumnsDoNotMatch : public std::exception {
private:
	std::string message;

public:
	ColumnsDoNotMatch(std::string msg) : message(msg) {}

	const char* what() const noexcept override {
		return message.c_str();
	}
};

class ColumnDoesNotExits : public std::exception {
private:
	std::string message;

public:
	ColumnDoesNotExits(std::string msg) : message(msg) {}

	const char* what() const noexcept override {
		return message.c_str();
	}
};

class DatabaseNotExist : public std::exception {
private:
	std::string message;

public:
	DatabaseNotExist(std::string msg) : message(msg) {}

	const char* what() const noexcept override {
		return message.c_str();
	}
};

class FileNotExist : public std::exception {
private:
	std::string message;

public:
	FileNotExist(std::string msg) : message(msg) {}

	const char* what() const noexcept override {
		return message.c_str();
	}
};

#endif