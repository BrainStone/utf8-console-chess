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

		Printer printer{};

		const bool stdinPipe = printer.isStdinPipe();
		bool useStdin = false;
		bool doubleSize = false;
		bool invertBoard = false;

		std::optional<std::string> file;
		std::optional<std::string> fen;

		auto parser = argumentum::argument_parser{};
		auto params = parser.params();
		parser.config().program(cmd).description(
		    "A little application to render FEN positions in the console with UTF-8 characters.");
		params.add_exclusive_group("fen source")
		    .title("FEN source")
		    .description(
		        "Specify one of the following sources for the FEN. If stdin is a pipe, `--stdin` is used per default.")
		    .required(!stdinPipe);
		params.add_parameter(file, "-f", "--file")
		    .nargs(1)
		    .metavar("FILE")
		    .help(
		        "Instead of from the arguments, read the FEN from FILE, or when FILE is -, read from standard input.");
		params.add_parameter(useStdin, "--stdin").help("Equivalent to `-f -`.");
		params.add_parameter(fen, "-F", "--fen").nargs(1).metavar("FEN").help("The FEN provided as a single string");
		params.end_group();
		params.add_parameter(doubleSize, "-d", "--double-size")
		    .help("Print the chess board in a larger font. This may not be supported by all consoles.");
		params.add_parameter(invertBoard, "-i", "--invert-board").help("Print the board from black's perspective.");
		params.add_default_help_option();

		auto parse_result = parser.parse_args(argc, argv, 1);

		if (!parse_result) {
			const bool error = parse_result.errors_were_shown();
			std::ostream& out = error ? std::cerr : std::cout;

			if (!parse_result.help_was_shown()) {
				parser.getConfig().help_formatter("")->format(parser.getDefinition(), out);
			}

			return error ? EXIT_FAILURE : EXIT_SUCCESS;
		}

		if (!printer.prepareConsole()) {
			return EXIT_FAILURE;
		}

		// If stdinPipe is true and file and fen are both not set, default to stdin mode
		useStdin = useStdin || (stdinPipe && !file && !fen);
		// If file is "-", set stdin mode
		useStdin = useStdin || (file && *file == "-");

		if (doubleSize) printer.setPrintDoubleSizeChars();

		ChessPosition pos;

		try {
			if (useStdin) {
				pos = FENReader::parseFEN(std::cin);
			} else if (file) {
				if (!std::filesystem::exists(*file)) {
					std::cerr << cmd << ": " << *file << ": No such file or directory" << std::endl;

					return EXIT_FAILURE;
				} else if (std::filesystem::is_directory(*file)) {
					std::cerr << cmd << ": " << *file << ": Is a directory" << std::endl;

					return EXIT_FAILURE;
				}

				std::ifstream input{*file};

				pos = FENReader::parseFEN(input);
			} else if (fen) {
				pos = FENReader::parseFEN(*fen);
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
