#pragma once

#include <sstream>

class Printer {
private:
	bool printDoubleSize;
	std::stringstream buffer;

public:
	Printer();

	void setPrintDoubleSizeChars(bool printDoubleSize = true);

	bool isStdinPipe() const;
	bool prepareConsole() const;

	template <class T>
	Printer& operator<<(const T& obj) {
		buffer << obj;

		return *this;
	}

	template <class T>
	Printer& operator<<(T& obj) {
		buffer << obj;

		return *this;
	}

	friend std::ostream& operator<<(std::ostream& stream, Printer& printer);
};
