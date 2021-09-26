/*
 * board.hpp
 *
 *  Created on: Sep 21, 2021
 *      Author: tim
 */

#ifndef BOARD_HPP_
#define BOARD_HPP_

using namespace std;

#include <string.h>
#include <iostream>
#include <vector>

class Board {
	char board[64];
	int directions[8][2] = { { -1, 0 }, { -1, -1 }, { -1, 1 }, { 1, 0 },
			{ 1, -1 }, { 1, 1 }, { 0, -1 }, { 0, 1 } };

public:
	Board(char ourColor);
	char getPiece(int row, int col);
	bool setPiece(int row, int col, char color);
	bool setPiece(char row, int col, char color);
	bool setPiece(int boardPos, char color);
	string boardToStr();
	int getPieceNumFromCoords(int row, int col);
	vector<int> flippedPieces(int row, int col, char color);
	void testCases();
	bool isGameOver();
	float utility();
	float evaluate();
};

#endif /* BOARD_HPP_ */
