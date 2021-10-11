#include "u8cc.h"

#include <iostream>

#include "printer.h"

int main() {
	if (!prepareConsole()) {
		return 1;
	}

	std::wcout << L"\033#3Test\n\033#4Test" << std::endl;

	return 0;
}
