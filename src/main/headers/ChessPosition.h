#pragma once

#include <array>
#include <string>

class ChessPosition {
public:
	class Piece {
	public:
		enum class PieceType : int8_t { NONE = 0, PAWN = 1, KNIGHT, BISHOP, ROOK, QUEEN, KING };
		enum class Color : int8_t { BLACK = -1, EMPTY = 0, WHITE = 1 };

	private:
		int8_t data;

	public:
		Piece(PieceType pieceType, Color color);
		Piece(char letter);
		Piece();

	private:
		static int8_t pieceTypeAndColorToInt(PieceType pieceType, Color color);
		static int8_t letterToInt(char letter);

	public:
		Piece& set(PieceType pieceType, Color color);
		Piece& set(char letter);
		Piece& set();

		PieceType getPieceType() const;
		Color getColor() const;

		std::string getUtf8ChessChar(Color backgroundColor) const;
	};

private:
	std::array<std::array<Piece, 8>, 8> position;

public:
	static ChessPosition getStartingPosition();

	ChessPosition& setPiece(Piece piece, char file, uint8_t rank);
	Piece& getPiece(char file, uint8_t rank);
	const Piece& getPiece(char file, uint8_t rank) const;
};
