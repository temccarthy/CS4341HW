/*
 * minimax.cpp
 *
 *  Created on: Sep 25, 2021
 *      Author: tim
 */

#include "minimax.hpp"
#include "timercpp.hpp"

Minimax::Minimax(float a, float b, char color){
	alpha = a;
	beta = b;
	timeUp = false;
	ourColor = color;
	if(ourColor == 'b'){
		opponentColor = 'o';
	}else{
		opponentColor = 'b';
	}
	iterativeLimit = 1;
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

	UtilityMovePair* pair;
	while(!timeUp){
		pair = maxValue(board, 0, 0);
		iterativeLimit ++;
	}
	
	return (*pair).move;
}


// tries to get best move for us (maximize utility)
UtilityMovePair* Minimax::maxValue(Board* board, int moveToMake, int ply) {
	// TODO: iterative deepening - iteratively limit the depth we go to (and call eval) and try again until time

	cout << "ply: " << ply << endl;
	if(ply >= iterativeLimit){
		//run eval function on board and return its evaluation score and piece index when we've reached the iterative limit

		UtilityMovePair* evaledMove = new UtilityMovePair(moveToMake, board->evaluate());
		ply = 0;
		cout << "hit iterative limit " << endl;
		return evaledMove;
	}
	// if game over, return utility value with null move
	if (board->isGameOver()){
		UtilityMovePair* ret = new UtilityMovePair(0, board->utility());
		cout << "gameover utility: " << ret->utility << endl;
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
			cout << board->ourColor << " move at " << i << endl << boardCopy->boardToStr() << endl;

			// try to find opponent's best move (which minimizes utility)
			if (ply==1){
				currMove = minValue(boardCopy, i, (ply+1));
			}else{
				currMove = minValue(boardCopy, moveToMake, (ply+1));
			}
			currMove->move = i;

			// if the new move has a better value, the chosen move becomes the new move
			if (currMove->utility > chosenMove->utility) {
				chosenMove = currMove;
				alpha = max(alpha, chosenMove->utility); // set alpha
			}

			// ab pruning - skips rest of the checks bc the child mins aren't bigger than this max
			if (chosenMove->utility >= beta) {
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
UtilityMovePair* Minimax::minValue(Board* board, int moveToMake, int ply) {
	// if out of time, start evaluating board instead of generating more moves

	if(ply >= iterativeLimit){
		//run eval function on board and return its evaluation score and piece index when we've reached the iterative limit

		UtilityMovePair* evaledMove = new UtilityMovePair(moveToMake, board->evaluate());
		cout << "hit iterative limit " << endl;
		return evaledMove;
	}
	// if game over, return utility value with null move
	if (board->isGameOver()){
		UtilityMovePair* ret = new UtilityMovePair(0, board->utility()); // 0 should be null
		cout << "gameover utility: " << ret->utility << endl;
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
			cout << board->opponentColor << " move at " << i << endl << boardCopy->boardToStr() << endl;

			// try to find opponent's best move (which minimizes utility)
			currMove = maxValue(boardCopy,moveToMake, (ply+1));
			currMove->move = i;

			// if the new move has a lower value, the chosen move becomes the new move
			if (currMove->utility < chosenMove->utility) {
				chosenMove = currMove;
				beta = min(beta, chosenMove->utility); // set beta
			}

			// ab pruning - skips rest of the checks bc the child mins aren't bigger than this max
			if (chosenMove->utility <= alpha) {
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
