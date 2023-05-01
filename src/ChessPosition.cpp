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
	letter = (char)std::toupper(letter);

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
		return pieceTypeAndColorToInt(PieceType::QUEEN, color);
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

std::string_view ChessPosition::Piece::getUtf8ChessChar(Color backgroundColor) const {
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
	case PieceType::QUEEN:
		return filled ? "♛" : "♕";
	case PieceType::KING:
		return filled ? "♚" : "♔";
	default:
		return " ";
	}
}

ChessPosition ChessPosition::getStartingPosition() {
	ChessPosition position{};

	Piece::Color color;
	for (uint8_t rank = 1; rank <= 8; rank += 7) {
		color = (rank == 1) ? Piece::Color::WHITE : Piece::Color::BLACK;

		position.setPiece({Piece::PieceType::ROOK, color}, 'a', rank)
		    .setPiece({Piece::PieceType::KNIGHT, color}, 'b', rank)
		    .setPiece({Piece::PieceType::BISHOP, color}, 'c', rank)
		    .setPiece({Piece::PieceType::QUEEN, color}, 'd', rank)
		    .setPiece({Piece::PieceType::KING, color}, 'e', rank)
		    .setPiece({Piece::PieceType::BISHOP, color}, 'f', rank)
		    .setPiece({Piece::PieceType::KNIGHT, color}, 'g', rank)
		    .setPiece({Piece::PieceType::ROOK, color}, 'h', rank);
	}

	for (char file = 'a'; file <= 'h'; ++file) {
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
	file = (char)std::tolower(file);

	return position[file - 'a'][rank - 1];
}

const ChessPosition::Piece& ChessPosition::getPiece(char file, uint8_t rank) const {
	file = (char)std::tolower(file);

	return position[file - 'a'][rank - 1];
}
