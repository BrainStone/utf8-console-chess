#include "u8cc.h"

#include <iostream>

#include "Printer.h"

int main() {
	Printer printer{};

	if (!printer.prepareConsole()) {
		return 1;
	}

	printer.setPrintDoubleSizeChars();

	printer << L'x' << L"XXX";
	std::wcout << printer;

	printer << L"Line 1\nLine 2";
	std::wcout << printer;

	return 0;
}
