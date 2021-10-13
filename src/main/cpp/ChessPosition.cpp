#include "ChessPosition.h"

#include <cctype>
#include <cmath>

ChessPosition::Piece::Piece(PieceType pieceType, Color color) : data(pieceTypeAndColorToInt(pieceType, color)) {}

ChessPosition::Piece::Piece(char letter) : data(letterToInt(letter)) {}

ChessPosition::Piece::Piece() : Piece(PieceType::NONE, Color::EMPTY) {}

int8_t ChessPosition::Piece::pieceTypeAndColorToInt(PieceType pieceType, Color color) {
	return static_cast<int8_t>(pieceType) * static_cast<int8_t>(color);
}

int8_t ChessPosition::Piece::letterToInt(char letter) {
	const Color color = std::isupper(letter) ? Color::WHITE : Color::BLACK;
	letter = std::toupper(letter);

	switch (letter) {
	case 'P':
		return pieceTypeAndColorToInt(PieceType::PAWN, color);
	case 'N':
		return pieceTypeAndColorToInt(PieceType::KNIGHT, color);
	case 'B':
		return pieceTypeAndColorToInt(PieceType::BISHOP, color);
	case 'R':
		return pieceTypeAndColorToInt(PieceType::ROOK, color);
	case 'Q':
		return pieceTypeAndColorToInt(PieceType::QUUEN, color);
	case 'K':
		return pieceTypeAndColorToInt(PieceType::KING, color);
	default:
		return pieceTypeAndColorToInt(PieceType::NONE, Color::EMPTY);
	}
}

ChessPosition::Piece& ChessPosition::Piece::set(PieceType pieceType, Color color) {
	data = pieceTypeAndColorToInt(pieceType, color);

	return *this;
}

ChessPosition::Piece& ChessPosition::Piece::set(char letter) {
	data = letterToInt(letter);

	return *this;
}

ChessPosition::Piece& ChessPosition::Piece::set() {
	return set(PieceType::NONE, Color::EMPTY);
}

ChessPosition::Piece::PieceType ChessPosition::Piece::getPieceType() const {
	return static_cast<PieceType>(std::abs(data));
}

ChessPosition::Piece::Color ChessPosition::Piece::getColor() const {
	if (data < 0) return Color::BLACK;
	if (data > 0) return Color::WHITE;
	return Color::EMPTY;
}

std::string ChessPosition::Piece::getUtf8ChessChar(Color backgroundColor) const {
	const Color color = getColor();

	if (color == Color::EMPTY) return " ";

	const PieceType type = getPieceType();
	const bool filled = (color != backgroundColor);

	switch (type) {
	case PieceType::PAWN:
		return filled ? "♟" : "♙";
	case PieceType::KNIGHT:
		return filled ? "♞" : "♘";
	case PieceType::BISHOP:
		return filled ? "♝" : "♗";
	case PieceType::ROOK:
		return filled ? "♜" : "♖";
	case PieceType::QUUEN:
		return filled ? "♛" : "♕";
	case PieceType::KING:
		return filled ? "♚" : "♔";
	default:
		return " ";
	}
}

ChessPosition ChessPosition::getStartingPosition() {
	ChessPosition position{};

	for (char file = 'A'; file <= 'H'; ++file) {
		position.setPiece({Piece::PieceType::PAWN, Piece::Color::WHITE}, file, 2)
		    .setPiece({Piece::PieceType::PAWN, Piece::Color::BLACK}, file, 7);
	}

	return position;
}

ChessPosition& ChessPosition::setPiece(Piece piece, char file, uint8_t rank) {
	getPiece(file, rank) = piece;

	return *this;
}

ChessPosition::Piece& ChessPosition::getPiece(char file, uint8_t rank) {
	file = std::toupper(file);

	return position[file - 'A'][rank - 1];
}

const ChessPosition::Piece& ChessPosition::getPiece(char file, uint8_t rank) const {
	file = std::toupper(file);

	return position[file - 'A'][rank - 1];
}
