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

class Board {
	char board[64];
	int directions[8][2] = { { -1, 0 }, { -1, -1 }, { -1, 1 }, { 1, 0 },
			{ 1, -1 }, { 1, 1 }, { 0, -1 }, { 0, 1 } };

public:
	Board(char ourColor);
	char getPiece(int row, int col);
	bool setPiece(int row, int col, char color);
	string boardToStr();
	int getPieceNumFromCoords(int row, int col);
	void testCases();
	bool gameOver();
	float utility();
	float evaluate();
private:
	;
};

#endif /* BOARD_HPP_ */
