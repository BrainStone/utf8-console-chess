#include "FENReader.h"

#include <sstream>

using namespace std::string_literals;

namespace FENReader {

ChessPosition parseFEN(const std::string& input) {
	std::istringstream inputStream{input};

	return parseFEN(inputStream);
}

ChessPosition parseFEN(std::istream& input) {
	using Color = ChessPosition::Piece::Color;
	using PieceType = ChessPosition::Piece::PieceType;

	ChessPosition position{};

	uint8_t rank = 8;
	char file = 'a';
	ChessPosition::Piece piece;
	bool wasDigit = false;

	char read;

	while (input) {
		read = input.get();

		// Check stream state after reading
		if (!input) break;

		if (read == ' ') {
			if (file != 'i') throw FENParseException{"Premature end of rank", file, rank};
			if (rank != 1) throw FENParseException{"Premature end of position (too little ranks)", file, rank};

			// End of position
			break;
		} else if ((read >= '1') && (read <= '8')) {
			if (wasDigit) throw FENParseException{"Digits can not be repeated", file, rank};

			file += read - '0';

			if (file > 'i') {
				// Undo addition
				file -= read - '0';

				throw FENParseException{"Too many empty squares ("s + read + ')', file, rank};
			}

			wasDigit = true;
		} else {
			if (read == '/') {
				if (file != 'i') throw FENParseException{"Premature end of rank", file, rank};
				if (rank == 1) throw FENParseException{"Too many ranks", file, rank};

				--rank;
				file = 'a';
			} else {
				piece = ChessPosition::Piece{read};

				if ((piece.getColor() == Color::EMPTY) || (piece.getPieceType() == PieceType::NONE))
					throw FENParseException{"Unknown piece ("s + read + ')', file, rank};

				position.setPiece(piece, file, rank);

				++file;
			}

			wasDigit = false;
		}
	}

	if (!input) throw FENParseException{"Premature end of position (stream error flag set)", file, rank};

	return position;
}

FENParseException::FENParseException(const std::string& message, char file, uint8_t rank)
    : FENParseException(message + getParsePostion(file, rank)) {}

FENParseException::FENParseException(const char* message, char file, uint8_t rank)
    : FENParseException(message + getParsePostion(file, rank)) {}

FENParseException::FENParseException(const std::string& message) : std::invalid_argument(message) {}

FENParseException::FENParseException(const char* message) : std::invalid_argument(message) {}

std::string FENParseException::getParsePostion(char file, uint8_t rank) {
	return " (while parsing postion "s + file + std::to_string(rank) + ')';
}

}  // namespace FENReader
