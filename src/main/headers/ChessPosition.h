#pragma once

#include <array>

class ChessPosition {
public:
	class Piece {
	public:
		enum class PieceType : int8_t { NONE = 0, PAWN = 1, KNIGHT, BISHOP, ROOK, QUUEN, KING };
		enum class Color : int8_t { BLACK = -1, EMPTY = 0, WHITE = 1 };

	private:
		int8_t data;

	public:
		Piece(PieceType pieceType, Color color);
		Piece(wchar_t letter);
		Piece();

	private:
		static int8_t pieceTypeAndColorToInt(PieceType pieceType, Color color);
		static int8_t letterToInt(wchar_t letter);

	public:
		Piece& set(PieceType pieceType, Color color);
		Piece& set(wchar_t letter);
		Piece& set();

		PieceType getPieceType() const;
		Color getColor() const;

		wchar_t getUtf8ChessChar(Color backgroundColor) const;
	};

private:
	std::array<std::array<Piece, 8>, 8> position;

public:
	static ChessPosition getStartingPosition();

	ChessPosition& setPiece(Piece piece, char file, uint8_t rank);
	Piece& getPiece(char file, uint8_t rank);
	const Piece& getPiece(char file, uint8_t rank) const;
};
