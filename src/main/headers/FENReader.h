#pragma once

#include <istream>
#include <stdexcept>
#include <string>

#include "ChessPosition.h"

namespace FENReader {

ChessPosition parseFEN(const std::string& input);
ChessPosition parseFEN(std::istream& input);

class FENParseException : public std::invalid_argument {
public:
	explicit FENParseException(const std::string& message, char file, uint8_t rank);
	explicit FENParseException(const char* message, char file, uint8_t rank);

	explicit FENParseException(const std::string& message);
	explicit FENParseException(const char* message);

	private:
	static std::string getParsePostion(char file, uint8_t rank);
};

}  // namespace FENReader
