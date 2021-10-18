#pragma once

#include "ChessPosition.h"
#include "Printer.h"

class ChessBoard {
private:
	ChessPosition position;
	bool whitePerspective;

public:
	ChessBoard(const ChessPosition& position, bool whitePerspective = true);
	ChessBoard(bool whitePerspective = true);

	friend Printer& operator<<(Printer& printer, const ChessBoard& board);
};
