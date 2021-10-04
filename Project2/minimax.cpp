/*
 * minimax.cpp
 *
 *  Created on: Sep 25, 2021
 *      Author: tim
 */

#include "minimax.hpp"

Minimax::Minimax(int tl){
	timeLimit = tl;
	timeUp = false;
}

// runs search, returns a move within ~9 seconds
int Minimax::minimaxSearch(Board* board, int ITL, Timer* t) {
	cout << "starting minimax search w/ ITL = " << ITL << endl;
		
	UtilityMovePair* pair;
	pair = maxValue(board, 0, ITL, -100, 100, t); // start minimax recursion

	return pair->move;
}

// tries to get best move for us (maximize utility)
UtilityMovePair* Minimax::maxValue(Board* board, int ply, int ITL, float alpha, float beta, Timer* t) {
	// stop recursion if out of time - return junk so we can use last completed iterative deepening result
	if (t->elapsedMilliseconds() >= timeLimit){
		timeUp = true;
		UtilityMovePair* unfinished = new UtilityMovePair(-1, 1000);
		free(board);
		// cout << "timer finished" << endl;
		return unfinished;
	}

	// stop recursion if iterative deepening limit reached - return evaluation of board 
	if(ply >= ITL){
		UtilityMovePair* evaledMove = new UtilityMovePair(0, board->evaluate());
		free(board);
		return evaledMove;
	}
	// stop recursion if gameOver - return utility of board
	if (board->isGameOver()){
		UtilityMovePair* ret = new UtilityMovePair(0, board->utility());
		// cout << "gameover utility: " << ret->utility << endl;
		free(board);
		return ret;
	}

	UtilityMovePair* chosenMove = new UtilityMovePair(0, -100.0); // minimax value at this stage of the tree (a, v in the pseudocode)
	UtilityMovePair* currMove; // move to be returned (a2, v2 in the pseudocode)
	Board* boardCopy = new Board(*board);

	// iterate through all moves by seeing if setPiece is true
	for (int i : moveOrder){

		// if board can setPiece
		if (boardCopy->setPiece(i/8, i%8, board->ourColor)){

			// try to find opponent's best move (which minimizes utility)
			currMove = minValue(boardCopy, ply+1, ITL, alpha, beta, t);
			currMove->move = i; // set the move value (was originally returned as 0)

			// if the new move has a better value, the chosen move becomes the new move
			if (currMove->utility > chosenMove->utility) {
				chosenMove = currMove;
				alpha = max(alpha, chosenMove->utility); // set alpha
			}

			// ab pruning
			if (chosenMove->utility >= beta) {
				// cout << "beta cut!" << endl;
				return chosenMove;
			}

			// resets board for trying next possible setPiece
			boardCopy = board->copyBoard();
		}
	}

	// return the move with the best utility
	return chosenMove;
}

// tries to get best move for opponents (minimizes utility)
UtilityMovePair* Minimax::minValue(Board* board, int ply, int ITL, float alpha, float beta, Timer* t) {
	// stop recursion if out of time - return junk so we can use last completed iterative deepening result
	if (t->elapsedMilliseconds() >= timeLimit){
		timeUp = true;
		UtilityMovePair* unfinished = new UtilityMovePair(-1, -1000);
		free(board);
		// cout << "timer finished" << endl;
		return unfinished;
	}

	// stop recursion if iterative deepening limit reached - return evaluation of board 
	if(ply >= ITL){
		UtilityMovePair* evaledMove = new UtilityMovePair(0, board->evaluate());
		free(board);
		return evaledMove;
	}
	// stop recursion if gameOver - return utility of board
	if (board->isGameOver()){
		UtilityMovePair* ret = new UtilityMovePair(0, board->utility());
		// cout << "gameover utility: " << ret->utility << endl;
		free(board);
		return ret;
	}

	UtilityMovePair* chosenMove = new UtilityMovePair(0, 100.0); // minimax value at this stage of the tree (a, v in the pseudocode)
	UtilityMovePair* currMove; // move to be returned (a2, v2 in the pseudocode)
	Board* boardCopy = new Board(*board);

	// iterate through all moves by seeing if setPiece is true
	for (int i : moveOrder){

		// if board can setPiece
		if (boardCopy->setPiece(i/8, i%8, board->opponentColor)){
			// cout << board->opponentColor << " move at " << i << endl << boardCopy->boardToStr() << endl;

			// try to find opponent's best move (which minimizes utility)
			currMove = maxValue(boardCopy, (ply+1), ITL, alpha, beta, t);
			currMove->move = i; // set the move value (was originally returned as 0)

			// if the new move has a lower value, the chosen move becomes the new move
			if (currMove->utility < chosenMove->utility) {
				chosenMove = currMove;
				beta = min(beta, chosenMove->utility); // set beta
			}

			// ab pruning
			if (chosenMove->utility <= alpha) {
				// cout << "alpha cut!" << endl;
				return chosenMove;
			}

			// resets board for trying next possible setPiece
			boardCopy = board->copyBoard();
		}
	}

	// return the move with the worst utility
	return chosenMove;
}
