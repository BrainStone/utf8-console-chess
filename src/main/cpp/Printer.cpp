#include "Printer.h"

#include <iostream>

#ifdef _WIN32
#include <Windows.h>
#endif

Printer::Printer() : printDoubleSize(false) {}

bool Printer::supportsDoubleSizeChars() {
#ifdef _WIN32
	return false;
#else
	return true;
#endif
}

void Printer::setPrintDoubleSizeChars(bool printDoubleSize) {
	this->printDoubleSize = printDoubleSize && supportsDoubleSizeChars();
}

bool Printer::prepareConsole() {
#ifdef _WIN32
	//SetConsoleOutputCP(CP_UTF8);

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if (hOut == INVALID_HANDLE_VALUE) {
		std::cerr << "Error in GetStdHandle (" << GetLastError() << ')' << std::endl;
		return false;
	}

	DWORD dwMode = 0;
	if (!GetConsoleMode(hOut, &dwMode)) {
		std::cerr << "Error in GetConsoleMode (" << GetLastError() << ')' << std::endl;
		return false;
	}

	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

	if (!SetConsoleMode(hOut, dwMode)) {
		std::cerr << "Error in SetConsoleMode (" << GetLastError() << ')' << std::endl;
		return false;
	}
#endif

	return true;
}

std::ostream& operator<<(std::ostream& stream, Printer& printer) {
	for (std::string line; std::getline(printer.buffer, line);) {
		if (printer.printDoubleSize) {
			stream << "\033#3" << line << '\n';
			stream << "\033#4" << line << '\n';
		} else {
			stream << line << '\n';
		}
	}

	stream.flush();
	printer.buffer.clear();

	return stream;
}
