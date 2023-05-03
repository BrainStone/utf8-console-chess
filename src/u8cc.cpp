#include "u8cc.hpp"

#include <argumentum/argparse.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>

#include "ChessBoard.hpp"
#include "FENReader.hpp"
#include "Printer.hpp"

int main(int argc, char* argv[]) {
	try {
		const std::string_view cmd = argv[0];

		bool useFile = false;
		bool doubleSize = false;
		bool invertBoard = false;

		std::optional<std::string> file;
		std::optional<std::string> fen;

		auto parser = argumentum::argument_parser{};
		auto params = parser.params();
		parser.config().program(cmd).description(
		    "A little application to render FEN positions in the console with UTF-8 characters.");
		params.add_parameter(file, "--file", "-f")
		    .metavar("FILE")
		    .help(
		        "Instead of from the arguments, read the FEN from FILE, or when FILE is -, read from standard input.");
		// --stdin           equivalent to -f -
		params.add_parameter(doubleSize, "-d", "--double-size")
		    .help("Print the chess board in a larger font. This may not be supported by all consoles.");
		params.add_parameter(invertBoard, "-i", "--invert-board").help("Print the board from black's perspective.");
		params.add_parameter(fen).metavar("FEN").help("The FEN provided as a single string");

		if (!parser.parse_args(argc, argv, 1)) {
			return EXIT_FAILURE;
		}

		Printer printer{};

		if (!printer.prepareConsole()) {
			return EXIT_FAILURE;
		}

		if (doubleSize) printer.setPrintDoubleSizeChars();

		ChessPosition pos;

		try {
			if (file) {
				if (*file == "-") {
					pos = FENReader::parseFEN(std::cin);
				} else {
					if (!std::filesystem::exists(*file)) {
						std::cerr << cmd << ": " << *file << ": No such file or directory" << std::endl;

						return EXIT_FAILURE;
					} else if (std::filesystem::is_directory(*file)) {
						std::cerr << cmd << ": " << *file << ": Is a directory" << std::endl;

						return EXIT_FAILURE;
					}

					std::ifstream input{*file};

					pos = FENReader::parseFEN(input);
				}
			} else if (fen) {
				pos = FENReader::parseFEN(*fen);
			} else {
				std::cerr << "Missing FEN\n\n";
				// printUsage(std::cerr, cmd);

				return EXIT_FAILURE;
			}
		} catch (const FENReader::FENParseException& e) {
			std::cerr << "Error while parsing FEN: " << e.what() << std::endl;

			return EXIT_FAILURE;
		}

		printer << ChessBoard{pos, !invertBoard};
		std::cout << printer << std::flush;

		return EXIT_SUCCESS;
	} catch (const std::exception& e) {
		std::cerr << "unexpected exception: " << e.what() << std::endl;

		return EXIT_FAILURE;
	}
}
