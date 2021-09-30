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
	char board[64]; // the board array
public:
	char ourColor; // which color we are
	char opponentColor; // opponent color


	Board();
	Board(Board* board);

	Board* copyBoard();

	void setOurColor(char color);

	char getPiece(int row, int col);
	int getPieceNumFromCoords(int row, int col);

	bool setPiece(int row, int col, char color);
	bool setPiece(char row, int col, char color);
	bool setPiece(int boardPos, char color);

	vector<int> flippedPieces(int row, int col, char color);

	bool isGameOver();
	float utility();
	float evaluate();
	int mobility(char color);
	int numberOfStableDiscs(char color);

	void testCases();
	string boardToStr();
};

#endif /* BOARD_HPP_ */
