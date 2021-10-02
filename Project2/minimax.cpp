/*
 * minimax.cpp
 *
 *  Created on: Sep 25, 2021
 *      Author: tim
 */

#include "minimax.hpp"
#include "timercpp.hpp"

Minimax::Minimax(float a, float b){
	alpha = a;
	beta = b;
	timeUp = false;
}

// runs search, returns a move within ~9 seconds
int Minimax::minimaxSearch(Board* board) {
	cout << "starting minimax search" << endl;
	Timer t = Timer();
	t.setTimeout([&]() {
		timeUp = true;
		cout << "times up!" << endl;
		t.stop();
	}, 9000);

	UtilityMovePair* pair = maxValue(board);
	return (*pair).move;
}

// tries to get best move for us (maximizes utility)
UtilityMovePair* Minimax::maxValue(Board* board) {
	// TODO: iterative deepening - iteratively limit the depth we go to (and call eval) and try again until time

	// if out of time, start evaluating board instead of generating more moves
	if (timeUp) {
		UtilityMovePair* ret = new UtilityMovePair(0, board->evaluate());
		cout << "timeUp evaluation: " << ret->utility << endl;
		free(board);
		return ret;
	}

	// if game over, return utility value with null move
	if (board->isGameOver()){
		UtilityMovePair* ret = new UtilityMovePair(0, board->utility());
		cout << "gameover utility: " << ret->utility << endl;
		free(board);
		return ret;
	}

	UtilityMovePair* chosenMove = new UtilityMovePair(0, -100.0); // minimax value at this stage of the tree (v, a in the pseudocode)
	UtilityMovePair* currMove; // move to be returned (v2, a2 in the pseudocode)
	Board* boardCopy = new Board(*board);

	// iterate through all moves by seeing if setPiece is true
	for (int i : moveOrder){

		// if board can setPiece
		if (boardCopy->setPiece(i/8, i%8, board->ourColor)){
			cout << board->ourColor << " move at " << i << endl << boardCopy->boardToStr() << endl;

			// try to find opponent's best move (which minimizes utility)
			currMove = minValue(boardCopy);
			currMove->move = i;

			// if the new move has a better value, the chosen move becomes the new move
			if (currMove->utility > chosenMove->utility) {
				chosenMove = currMove;
				alpha = max(alpha, chosenMove->utility); // set alpha
			}

			// ab pruning - skips rest of the checks bc the child mins aren't bigger than this max
			if ((*chosenMove).utility >= beta) {
				cout << "beta cut!" << endl;
				return chosenMove;
			}

			// resets board for trying next possible setPiece
//			cout << "new board\n" << boardCopy->boardToStr() << endl;
			boardCopy = board->copyBoard();
			//cout << " after\n" << boardCopy->boardToStr() << endl;

		}
	}

	// return the move with the best utility
	return chosenMove;
}

// tries to get best move for opponents (minimizes utility)
UtilityMovePair* Minimax::minValue(Board* board) {
	// if out of time, start evaluating board instead of generating more moves
	if (timeUp) {
		UtilityMovePair* ret = new UtilityMovePair(0, board->evaluate()); // 0 should be null
		cout << "timeUp evaluation: " << ret->utility << endl;
		free(board);
		return ret;
	}

	// if game over, return utility value with null move
	if (board->isGameOver()){
		UtilityMovePair* ret = new UtilityMovePair(0, board->utility()); // 0 should be null
		cout << "gameover utility: " << ret->utility << endl;
		free(board);
		return ret;
	}

	UtilityMovePair* chosenMove = new UtilityMovePair(0, 100.0); // minimax value at this stage of the tree (v, a in the pseudocode)
	UtilityMovePair* currMove; // move to be returned (v2, a2 in the pseudocode)
	Board* boardCopy = new Board(*board);

	// iterate through all moves by seeing if setPiece is true
	for (int i : moveOrder){

		// if board can setPiece
		if (boardCopy->setPiece(i/8, i%8, board->opponentColor)){
			cout << board->opponentColor << " move at " << i << endl << boardCopy->boardToStr() << endl;

			// try to find opponent's best move (which minimizes utility)
			currMove = maxValue(boardCopy);
			currMove->move = i;

			// if the new move has a lower value, the chosen move becomes the new move
			if (currMove->utility < chosenMove->utility) {
				chosenMove = currMove;
				beta = min(beta, chosenMove->utility); // set beta
			}

			// ab pruning - skips rest of the checks bc the child mins aren't bigger than this max
			if ((*chosenMove).utility <= alpha) {
				cout << "alpha cut!" << endl;
				return chosenMove;
			}

			// resets board for trying next possible setPiece
//			cout << "new board\n" << boardCopy->boardToStr() << endl;
			boardCopy = board->copyBoard();
			//cout << " after\n" << boardCopy->boardToStr() << endl;

		}
	}

	// return the move with the best utility
	return chosenMove;
}
