#include "u8cc.h"

#include <iostream>

#include "ChessPosition.h"
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

	ChessPosition position{ChessPosition::getStartingPosition()};

	for (uint8_t rank = 8; rank >= 1; --rank) {
		for (char file = 'a'; file <= 'h'; ++file) {
			printer << position.getPiece(file, rank).getUtf8ChessChar(ChessPosition::Piece::Color::BLACK);
		}

		printer << '\n';
	}

	std::cout << printer;

	return 0;
}
