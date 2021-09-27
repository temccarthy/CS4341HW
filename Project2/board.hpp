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

public:
	Board(char ourColor);
	Board(Board* board);
	Board* copyBoard();

	char getPiece(int row, int col);
	bool setPiece(int row, int col, char color);
	bool setPiece(char row, int col, char color);
	bool setPiece(int boardPos, char color);
	string boardToStr();
	int getPieceNumFromCoords(int row, int col);
	vector<int> flippedPieces(int row, int col, char color);
	void testCases();
	bool isGameOver();
	float utility(char color);
	float evaluate(char color);
};

#endif /* BOARD_HPP_ */
