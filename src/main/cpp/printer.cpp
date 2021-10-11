#include "printer.h"

#include <iostream>

#ifdef _WIN32
#include <Windows.h>
#endif

bool supportsDoubleSizeChars() {
#ifdef _WIN32
	return false;
#else
	return true;
#endif
}

bool prepareConsole() {
#ifdef _WIN32
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
