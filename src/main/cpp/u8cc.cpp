#include "u8cc.h"

#include <filesystem>
#include <fstream>
#include <iostream>

#include "ChessBoard.h"
#include "FENReader.h"
#include "Printer.h"

int main(int argc, char* argv[]) {
	try {
		std::string cmd{argv[0]};

		std::vector<std::string> args;
		args.reserve(argc - 1);
		args.assign(argv + 1, argv + argc);

		return stlMain(std::move(cmd), std::move(args));
	} catch (const std::exception& e) {
		std::cerr << "unexpected exception: " << e.what() << std::endl;

		return EXIT_FAILURE;
	}
}

int stlMain(std::string&& cmd, std::vector<std::string>&& args) {
	bool useFile = false;
	bool doubleSize = false;
	bool invertBoard = false;

	std::string file;
	std::string fen;

	if (!parseArgs(cmd, args, useFile, doubleSize, invertBoard, file, fen)) return EXIT_FAILURE;

	Printer printer{};

	if (!printer.prepareConsole()) {
		return EXIT_FAILURE;
	}

	if (doubleSize) printer.setPrintDoubleSizeChars();

	ChessPosition pos;

	try {
		if (useFile) {
			if (file == "-") {
				pos = FENReader::parseFEN(std::cin);
			} else {
				if (!std::filesystem::exists(file)) {
					std::cerr << cmd << ": " << file << ": No such file or directory" << std::endl;

					return EXIT_FAILURE;
				} else if (std::filesystem::is_directory(file)) {
					std::cerr << cmd << ": " << file << ": Is a directory" << std::endl;

					return EXIT_FAILURE;
				}

				std::ifstream input{file};

				pos = FENReader::parseFEN(input);
			}
		} else {
			pos = FENReader::parseFEN(fen);
		}
	} catch (const FENReader::FENParseException& e) {
		std::cerr << "Error while parsing FEN: " << e.what() << std::endl;

		return EXIT_FAILURE;
	}

	printer << ChessBoard{pos, !invertBoard};
	std::cout << printer << std::flush;

	return EXIT_SUCCESS;
}

bool parseArgs(const std::string& cmd, const std::vector<std::string>& args, bool& useFile, bool& doubleSize,
               bool& invertBoard, std::string& file, std::string& fen) {
	std::vector<std::string>::const_iterator it;

	for (it = args.cbegin(); it != args.cend(); ++it) {
		if ((*it == "-h") || (*it == "--help")) {
			printUsage(std::cout, cmd);

			return false;
		} else if ((*it == "-f") || (*it == "--file")) {
			if (++it == args.cend()) {
				std::cerr << "Missing FILE after " << *(--it) << "\n\n";
				printUsage(std::cerr, cmd);

				return false;
			}

			useFile = true;
			file = *it;
		} else if (*it == "--stdin") {
			useFile = true;
			file = "-";
		} else if ((*it == "-d") || (*it == "--double-size")) {
			doubleSize = true;
		} else if ((*it == "-i") || (*it == "--invert-board")) {
			invertBoard = true;
		} else if (*it == "--stdin") {
			// Ignore this arg but stop parsing flags
			++it;

			break;
		} else {
			break;
		}
	}

	if (!useFile) {
		if (it == args.cend()) {
			std::cerr << "Missing FEN\n\n";
			printUsage(std::cerr, cmd);

			return false;
		}

		fen = *it++;
	}

	if (it != args.cend()) {
		std::cerr << "Too many parameters\n\n";
		printUsage(std::cerr, cmd);

		return false;
	}

	return true;
}

void printUsage(std::ostream& console, const std::string& cmd) {
	console << "Usage: " << cmd << R"( [OPTION]... [FEN]
A little application to render FEN positions in the console with UTF-8 characters.

  -h, --help                 display this message and exit

  -f, --file FILE            instead of from the arguments, read the FEN from
                             FILE, or when FILE is -, read from standard input
      --stdin                equivalent to -f -

  -d, --double-size          print the chess board in a larger font. This may
                             not be supported by all consoles
  -i, --invert-board         print the board from black's perspective
)" << std::flush;
}
