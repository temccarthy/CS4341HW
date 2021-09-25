/*
 * minimax.cpp
 *
 *  Created on: Sep 25, 2021
 *      Author: tim
 */

#include "minimax.hpp"

// runs search
int Minimax::minimaxSearch(Board board) {
	int move = maxValue(board);
	return move;
}

// tries to get best move for us (maximize utility)
int Minimax::maxValue(Board board) {
	if (board.gameOver()){
		return board.utility();
	}
	float v = -100.0; // minimax value at this stage of the tree
	float v2 = 0;

	// iterate through possible moves by seeing if setPiece is true
	for (int i = 0; i < 64; i++){
		if (board.setPiece(i%8, i/8, 'o')){
			v2 = minValue(board);
			if (v2 > v) {
				v = v2;
			}
		}
	}
	return
}

// tries to get best move for opponents (minimizes utility)
int Minimax::minValue(Board board) {

}
