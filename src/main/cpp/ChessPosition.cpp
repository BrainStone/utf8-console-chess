#include "ChessPosition.h"

#include <cctype>
#include <cmath>

ChessPosition::Piece::Piece(PieceType pieceType, Color color) : data(pieceTypeAndColorToInt(pieceType, color)) {}

ChessPosition::Piece::Piece(wchar_t letter) : data(letterToInt(letter)) {}

ChessPosition::Piece::Piece() : Piece(PieceType::NONE, Color::EMPTY) {}

int8_t ChessPosition::Piece::pieceTypeAndColorToInt(PieceType pieceType, Color color) {
	return static_cast<int8_t>(pieceType) * static_cast<int8_t>(color);
}

int8_t ChessPosition::Piece::letterToInt(wchar_t letter) {
	const Color color = std::isupper(letter) ? Color::WHITE : Color::BLACK;
	letter = std::toupper(letter);

	switch (letter) {
	case L'P':
		return pieceTypeAndColorToInt(PieceType::PAWN, color);
	case L'N':
		return pieceTypeAndColorToInt(PieceType::KNIGHT, color);
	case L'B':
		return pieceTypeAndColorToInt(PieceType::BISHOP, color);
	case L'R':
		return pieceTypeAndColorToInt(PieceType::ROOK, color);
	case L'Q':
		return pieceTypeAndColorToInt(PieceType::QUUEN, color);
	case L'K':
		return pieceTypeAndColorToInt(PieceType::KING, color);
	default:
		return pieceTypeAndColorToInt(PieceType::NONE, Color::EMPTY);
	}
}

ChessPosition::Piece& ChessPosition::Piece::set(PieceType pieceType, Color color) {
	data = pieceTypeAndColorToInt(pieceType, color);

	return *this;
}

ChessPosition::Piece& ChessPosition::Piece::set(wchar_t letter) {
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

wchar_t ChessPosition::Piece::getUtf8ChessChar(Color backgroundColor) const {
	const Color color = getColor();

	if (color == Color::EMPTY) return L' ';

	const PieceType type = getPieceType();
	const bool filled = (color != backgroundColor);

	switch (type) {
	case PieceType::PAWN:
		return filled ? L'♟' : L'♙';
	case PieceType::KNIGHT:
		return filled ? L'♞' : L'♘';
	case PieceType::BISHOP:
		return filled ? L'♝' : L'♗';
	case PieceType::ROOK:
		return filled ? L'♜' : L'♖';
	case PieceType::QUUEN:
		return filled ? L'♛' : L'♕';
	case PieceType::KING:
		return filled ? L'♚' : L'♔';
	default:
		return L' ';
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
