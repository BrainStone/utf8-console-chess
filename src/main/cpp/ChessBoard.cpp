#include "ChessBoard.h"

const std::string reset = "\033[m";

const std::string whiteCellStr = "\033[27m";
const std::string blackCellStr = "\033[7m";

const std::string halfCell = "▐";
const std::string emptyCell = " ";

ChessBoard::ChessBoard(const ChessPosition& position, bool whitePerspective)
    : position(position), whitePerspective(whitePerspective) {}

ChessBoard::ChessBoard(bool whitePerspective) : ChessBoard(ChessPosition::getStartingPosition(), whitePerspective) {}

Printer& operator<<(Printer& printer, const ChessBoard& board) {
	using Color = ChessPosition::Piece::Color;

	int x, y;
	uint8_t rank;
	char file;
	bool whiteRow, whiteCell;

	for (y = 0; y < 8; ++y) {
		rank = board.whitePerspective ? (8 - y) : (1 + y);
		whiteRow = !(y & 1);

		printer << (int)rank << "  \033[;" << (whiteRow ? "37m" : "30m") << halfCell << "\033[30;47m";

		for (x = 0; x < 8; ++x) {
			file = board.whitePerspective ? ('a' + x) : ('h' - x);
			whiteCell = !((x ^ y) & 1);

			printer << (whiteCell ? whiteCellStr : blackCellStr)
			        << board.position.getPiece(file, rank).getUtf8ChessChar(whiteCell ? Color::WHITE : Color::BLACK);

			if (x != 7) {
				printer << halfCell;
			}
		}

		// Last cell is color inverted 
		printer << "\033[;" << (whiteRow ? "30m" : "37m") << "▌" << reset << '\n';
	}

	printer << "\n   ";

	for (x = 0; x < 8; ++x) {
		file = board.whitePerspective ? ('a' + x) : ('h' - x);

		printer << ' ' << file;
	}

	printer << '\n';
}
