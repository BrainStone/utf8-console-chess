#pragma once

#include <sstream>

class Printer {
private:
	bool printDoubleSize;
	std::wstringstream buffer;

public:
	Printer();

	bool supportsDoubleSizeChars();
	void setPrintDoubleSizeChars(bool printDoubleSize = true);

	bool prepareConsole();

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

	friend std::wostream& operator<<(std::wostream& stream, Printer& printer);
};
