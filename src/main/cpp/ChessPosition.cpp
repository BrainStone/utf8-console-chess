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

ChessPosition::Piece::PieceType ChessPosition::Piece::getPieceType() {
	return static_cast<PieceType>(std::abs(data));
}

ChessPosition::Piece::Color ChessPosition::Piece::getColor() {
	if (data < 0) return Color::BLACK;
	if (data > 0) return Color::WHITE;
	return Color::EMPTY;
}

wchar_t ChessPosition::Piece::getUtf8ChessChar(Color backgroundColor) {
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
