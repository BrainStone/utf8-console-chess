#include "u8cc.h"

#include <iostream>

#include "ChessBoard.h"
#include "FENReader.h"
#include "Printer.h"

int main(int argc, char* argv[]) {
	std::string cmd{argv[0]};

	std::vector<std::string> args;
	args.reserve(argc - 1);
	args.assign(argv + 1, argv + argc);

	return stlMain(std::move(cmd), std::move(args));
}

int stlMain([[maybe_unused]] std::string&& cmd, std::vector<std::string>&& args) {
	Printer printer{};

	if (!printer.prepareConsole()) {
		return 1;
	}

	printer.setPrintDoubleSizeChars();

	ChessPosition pos;

	try {
		pos = FENReader::parseFEN(args.at(0));
	} catch (const FENReader::FENParseException& e) {
		std::cerr << "FENParseException: " << e.what() << std::endl;

		return 1;
	} catch (const std::exception& e) {
		std::cerr << "exception: " << e.what() << std::endl;

		return 1;
	}

	printer << ChessBoard{pos, true};
	std::cout << '\n' << printer << "\n\n";

	printer << ChessBoard{pos, false};
	std::cout << printer << std::flush;

	return 0;
}
