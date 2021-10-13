#include "u8cc.h"

#include <algorithm>
#include <codecvt>
#include <iostream>
#include <locale>

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
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	std::wstring wcmd = converter.from_bytes(cmd);

	std::vector<std::wstring> wargs;
	wargs.reserve(args.size());
	std::transform(args.cbegin(), args.cend(), std::back_inserter(wargs),
	               [&converter](const std::string& str) { return converter.from_bytes(str); });

	return stlWMain(std::move(wcmd), std::move(wargs));
}

int stlWMain(std::wstring&& cmd, std::vector<std::wstring>&& args) {
	Printer printer{};

	if (!printer.prepareConsole()) {
		return 1;
	}

	printer.setPrintDoubleSizeChars();

	ChessPosition position{ChessPosition::getStartingPosition()};

	for (uint8_t rank = 1; rank <= 8; ++rank) {
		for (char file = 'A'; file <= 'H'; ++file) {
			printer << position.getPiece(file, rank).getUtf8ChessChar(ChessPosition::Piece::Color::BLACK);
		}

		printer << L'\n';
	}

	std::wcout << printer;

	return 0;
}
