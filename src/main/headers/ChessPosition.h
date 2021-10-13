#pragma once

#include <array>

class ChessPosition {
public:
	static class Piece {
	public:
		static enum class PieceType : int8_t { NONE = 0, PAWN = 1, KNIGHT, BISHOP, ROOK, QUUEN, KING };
		static enum class Color : int8_t { BLACK = -1, EMPTY = 0, WHITE = 1 };

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
		PieceType getPieceType();
		Color getColor();

		wchar_t getUtf8ChessChar(Color backgroundColor);
	};

private:
	std::array<std::array<Piece, 8>, 8> position;
};