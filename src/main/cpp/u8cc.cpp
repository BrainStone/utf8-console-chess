#include "u8cc.h"

#include <algorithm>
#include <codecvt>
#include <iostream>
#include <locale>

#include "Printer.h"

int main(int argc, char* argv[]) {
	std::string cmd{argv[0]};

	std::vector<std::string> args;
	args.reserve(argc - 1);
	args.assign(argv + 1, argv + argc);

	return stdMain(std::move(cmd), std::move(args));
}

int stdMain(std::string&& cmd, std::vector<std::string>&& args) {
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	std::wstring wcmd = converter.from_bytes(cmd);

	std::vector<std::wstring> wargs;
	wargs.reserve(args.size());
	std::transform(args.cbegin(), args.cend(), std::back_inserter(wargs),
	               [&converter](const std::string& str) { return converter.from_bytes(str); });

	return stdWMain(std::move(wcmd), std::move(wargs));
}

int stdWMain(std::wstring&& cmd, std::vector<std::wstring>&& args) {
	Printer printer{};

	if (!printer.prepareConsole()) {
		return 1;
	}

	printer.setPrintDoubleSizeChars();

	printer << L"My name is: " << cmd << L'\n';
	std::wcout << printer;

	printer << L"My parameters are:\n";
	for (const std::wstring& arg : args) {
		printer << L" - " << arg << L'\n';
	}
	std::wcout << printer;

	return 0;
}
