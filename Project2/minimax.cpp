/*
 * minimax.cpp
 *
 *  Created on: Sep 25, 2021
 *      Author: tim
 */

#include "minimax.hpp"

Minimax::Minimax(float a, float b, char color){
	alpha = a;
	beta = b;
	ourColor = color;
	if(ourColor == 'b'){
		opponentColor = 'o';
	}else{
		opponentColor = 'b';
	}

	iterativeLimit = 2;
	ply = 0;
}

// runs search, returns the move
int Minimax::minimaxSearch(Board* board) {
	// TODO: start a timer here, when timer over start evaluating moves instead of trying to get to the bottom of the tree
	cout << "starting minimax search" << endl;
	UtilityMovePair* pair = maxValue(board,0);
	return (*pair).move;
}

// tries to get best move for us (maximize utility)
UtilityMovePair* Minimax::maxValue(Board* board, int moveToMake) {
	// TODO: iterative deepening - iteratively limit the depth we go to (and call eval) and try again until time

	cout << "ply: " << ply << endl;
	if(ply >= iterativeLimit){
		//run eval function on board and return its evaluation score and piece index when we've reached the iterative limit

		UtilityMovePair* evaledMove = new UtilityMovePair(moveToMake, board->evaluate());
		ply = 0;
		cout << "hit iterative limit " << endl;
		return evaledMove;
	}else{
		ply++;
	}
	// if game over, return utility value with null move
	if (board->isGameOver()){
		UtilityMovePair* ret = new UtilityMovePair(0, board->utility()); // 0 should be null
		cout << "gameover utility: " << ret->utility << endl;
		free(board);
		return ret;
	}
	UtilityMovePair* chosenMove = new UtilityMovePair(0, -100.0); // minimax value at this stage of the tree (v, a in the pseudocode)
	UtilityMovePair* currMove; // move to be returned (v2, a2 in the pseudocode)
	Board* boardCopy = new Board(*board);

	// cout << "maxing board " << &boardCopy << endl;
	// iterate through possible moves by seeing if setPiece is true
	for (int i = 0; i < 64; i++){

		// if board can setPiece
		if (boardCopy->setPiece(i/8, i%8, ourColor)){ // TODO: figure out which piece we are
			cout << ourColor << " move at " << i << endl << boardCopy->boardToStr() << endl;

			// try to find opponent's best move (which minimizes utility)
			if (ply==1){
				currMove = minValue(boardCopy, i);
			}else{
				currMove = minValue(boardCopy, moveToMake);
			}
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
UtilityMovePair* Minimax::minValue(Board* board, int moveToMake) {

	ply++;

	// if game over, return utility value with null move
	if (board->isGameOver()){
		UtilityMovePair* ret = new UtilityMovePair(0, board->utility()); // 0 should be null
		cout << "gameover utility: " << ret->utility << endl;
		free(board);
		return ret;
	}
	UtilityMovePair* chosenMove = new UtilityMovePair(0, -100.0); // minimax value at this stage of the tree (v, a in the pseudocode)
	UtilityMovePair* currMove; // move to be returned (v2, a2 in the pseudocode)
	Board* boardCopy = new Board(*board);

	// cout << "minning board " << &boardCopy << endl;
	// iterate through possible moves by seeing if setPiece is true
	for (int i = 0; i < 64; i++){

		// if board can setPiece
		if (boardCopy->setPiece(i/8, i%8, opponentColor)){ // TODO: figure out which piece we
			cout << opponentColor << " move at " << i << endl << boardCopy->boardToStr() << endl;

			// try to find opponent's best move (which minimizes utility)
			currMove = maxValue(boardCopy,moveToMake);
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
