#include <cstdint>
#include <sstream>
#include <string>

#include "FENReader.hpp"
#include "gtest/gtest.h"

class TestFENReader : public ::testing::TestWithParam<std::string> {};

TEST_P(TestFENReader, StreamStringEquivalence) {
	const std::string fen = GetParam();
	std::istringstream fenSteam(fen);

	const ChessPosition pos1 = FENReader::parseFEN(fen);
	const ChessPosition pos2 = FENReader::parseFEN(fenSteam);

	for (uint8_t rank = 1; rank <= 8; ++rank) {
		for (char file = 'a'; file <= 'h'; ++file) {
			EXPECT_EQ(pos1.getPiece(file, rank), pos2.getPiece(file, rank));
		}
	}
}

INSTANTIATE_TEST_SUITE_P(FENTests, TestFENReader,
                         ::testing::Values(
                             // Constructed postions
                             "8/8/8/8/8/8/8/8 w - - 0 1",  //
                             "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
                             // Real games
                             "6k1/1pp3p1/1p1p1pP1/8/2PRr3/P7/1PPK1nP1/8 w - - 3 26",
                             "5r2/5pkQ/4pNp1/8/4NP2/4q1PK/1P5P/8 b - - 4 44"));
