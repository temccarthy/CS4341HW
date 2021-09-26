/*
 * minimax.cpp
 *
 *  Created on: Sep 25, 2021
 *      Author: tim
 */

#include "minimax.hpp"

// runs search, returns the move
int Minimax::minimaxSearch(Board* board) {
	UtilityMovePair* pair = maxValue(board);
	return (*pair).move;
}

// tries to get best move for us (maximize utility)
UtilityMovePair* Minimax::maxValue(Board* board) {
	// if game over, return utility value with null move
	if ((*board).isGameOver()){
		UtilityMovePair* ret = new UtilityMovePair(0, (*board).utility()); // 0 should be null
		return ret;
	}
	UtilityMovePair* chosenMove = new UtilityMovePair(0, -100.0); // minimax value at this stage of the tree (v, a in the pseudocode)
	UtilityMovePair* currMove; // move to be returned (v2, a2 in the pseudocode)
	Board* boardCopy = new Board(*board);

	// iterate through possible moves by seeing if setPiece is true
	for (int i = 0; i < 64; i++){
		// if board can setPiece
		if ((*boardCopy).setPiece(i/8, i%8, 'o')){ // TODO: figure out which piece we are

			// try to find opponent's best move (which minimizes utility)
			currMove = minValue(board);
			(*currMove).move = i;

			// if the new move has a better value, the chosen move becomes the new move
			if ((*currMove).utility > (*chosenMove).utility) {
				chosenMove = currMove;
				alpha = max(alpha, (*chosenMove).utility); // set alpha
			}

			// ab pruning - skips rest of the checks bc the child mins aren't bigger than this max
			if ((*chosenMove).utility >= beta) {
				return chosenMove;
			}

			// resets board for trying next possible setPiece
			Board* boardCopy = new Board(*board);
		}
	}

	// return the move with the best utility
	return chosenMove;
}

// tries to get best move for opponents (minimizes utility)
UtilityMovePair* Minimax::minValue(Board* board) {
	UtilityMovePair* chosenMove = new UtilityMovePair(0, 100.0);
	return chosenMove;
}
