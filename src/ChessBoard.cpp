#include "ChessBoard.hpp"

const std::string_view reset = "\033[m";

const std::string_view whiteCellStr = "\033[27m";
const std::string_view blackCellStr = "\033[7m";

const std::string_view halfCell = "▐";

ChessBoard::ChessBoard(const ChessPosition& position, bool whitePerspective)
    : position(position), whitePerspective(whitePerspective) {}

ChessBoard::ChessBoard(bool whitePerspective) : ChessBoard(ChessPosition::getStartingPosition(), whitePerspective) {}

std::ostream& operator<<(std::ostream& stream, const ChessBoard& board) {
	using Color = ChessPosition::Piece::Color;

	char x;
	uint8_t y;
	uint8_t rank;
	char file;
	bool whiteRow, whiteCell;

	for (y = 0; y < 8; ++y) {
		rank = board.whitePerspective ? (8 - y) : (1 + y);
		whiteRow = !(y & 1);

		stream << (int)rank << "  \033[;" << (whiteRow ? "37m" : "30m") << halfCell << "\033[30;47m";

		for (x = 0; x < 8; ++x) {
			file = board.whitePerspective ? ('a' + x) : ('h' - x);
			whiteCell = !((x ^ y) & 1);

			stream << (whiteCell ? whiteCellStr : blackCellStr)
			       << board.position.getPiece(file, rank).getUtf8ChessChar(whiteCell ? Color::WHITE : Color::BLACK);

			if (x != 7) {
				stream << halfCell;
			}
		}

		// Last cell is color inverted
		stream << "\033[;" << (whiteRow ? "30m" : "37m") << "▌" << reset << '\n';
	}

	stream << "\n   ";

	for (x = 0; x < 8; ++x) {
		file = board.whitePerspective ? ('a' + x) : ('h' - x);

		stream << ' ' << file;
	}

	stream << '\n';

	return stream;
}
