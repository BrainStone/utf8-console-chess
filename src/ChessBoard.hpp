#pragma once

#include <ostream>

#include "ChessPosition.hpp"

class ChessBoard {
private:
	ChessPosition position;
	bool whitePerspective;

public:
	ChessBoard(const ChessPosition& position, bool whitePerspective = true);
	ChessBoard(bool whitePerspective = true);

	friend std::ostream& operator<<(std::ostream& stream, const ChessBoard& board);
};
