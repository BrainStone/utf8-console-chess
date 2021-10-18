#include "u8cc.h"

#include <iostream>

#include "ChessBoard.h"
#include "Printer.h"

int main(int argc, char* argv[]) {
	std::string cmd{argv[0]};

	std::vector<std::string> args;
	args.reserve(argc - 1);
	args.assign(argv + 1, argv + argc);

	return stlMain(std::move(cmd), std::move(args));
}

int stlMain(std::string&& cmd, std::vector<std::string>&& args) {
	Printer printer{};

	if (!printer.prepareConsole()) {
		return 1;
	}

	printer.setPrintDoubleSizeChars();

	std::cout << '\n';

	ChessBoard board{true};

	printer << board;
	std::cout << printer << "\n\n";

	printer << ChessBoard{false};
	std::cout << printer << std::flush;

	return 0;
}
