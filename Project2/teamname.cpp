/*
 * teamname.cpp
 *
 *  Created on: Sep 20, 2021
 *      Author: tim
 */

using namespace std;

#include <iostream>
#include <string.h>
#include <fstream>
#include <sys/stat.h>
#include "board.hpp"
#include "minimax.hpp"
#include <thread>


string teamname = "teamname";

// from https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-14-17-c
inline bool goFileExists() {
	struct stat buffer;
	return (stat((teamname + ".go").c_str(), &buffer) == 0);
}


string readLastMove(fstream* fin) {
	string lastLine, prevLine;

	// stops reading before empty line
	// maybe need to refactor if other players mess move_file up
	while (getline(*fin, lastLine) && lastLine != ""){
		prevLine = lastLine;
//		if (fin->peek() == EOF) { // mess around with this?
//			break;
//		}
	}

	return prevLine;
}

char determineOurColor(fstream* fin) {
	string firstLine;

	//fin->seekg(0, fin->beg);

	if (fin->peek() == EOF) {
		return 'b'; // there's a move already so we go second so we're orange
	} else {
		return 'o'; // there's no moves in move_file so we go first so we're blue
	}
}

void writeOurMove(fstream* fin, int move) {
	fin->close();
	fin->open("move_file", ios::in | ios::app);

	char col = 65 + move%8;
	char row = 49 + move/8;
	string moveString = teamname + " " + col + " " + row + '\n';
	cout << "writing: " << moveString << endl;
	fin->write(moveString.data(), moveString.size());
	//*fin << moveString << endl;
}

int main() {

//	Board testBoard = Board();
//	//testBoard.setOurColor('o');
//	testBoard.setPiece('C', 5, 'b');
//	testBoard.setPiece('C', 4, 'o');
//	testBoard.setPiece(18, 'b');
//	testBoard.setPiece(44, 'o');
//	cout << testBoard.boardToStr() << endl;
//	testBoard.setPiece(19, 'b');
//
//	// testBoard.setPiece(26, 'b'); // 2,1
//	cout << "test board:" << endl;
//	cout << testBoard.boardToStr() << endl;


	bool playing = true;
	bool ourColorDetermined = false;

	Board b = Board();
	fstream move_file;
	string lastMove, opponentMove;
	int moveToMake, prevMoveToMake;
	int timeLimit = 9000; // 9000 milliseconds
	int ITL;
	Timer* t;

	while (playing) {
		// start by looking for name.go file
		while (!goFileExists()) {
			// spin while waiting
		}
		playing = false; // TODO: remove this later; test that multiple moves in a row works

		cout << "go file found; opening move_file" << endl;

		// open move_file and read last line
		move_file.open("move_file", ios::in | ios::app);

		if (!ourColorDetermined) {
			char ourCol = determineOurColor(&move_file);
			cout << "our color: " << ourCol << endl;
			b.setOurColor(ourCol);
			ourColorDetermined = true;

			if (ourCol == 'b') { // if no moves, we make a move first (doesn't matter which)
				cout << "our move first: 34" << endl;
				b.setPiece(34, 'b');
				cout << "new board:\n" << b.boardToStr() << endl;
				writeOurMove(&move_file, 34);
				continue;
			}
		} // TODO: if other player goes first, make their move, otherwise skip that part

		lastMove = readLastMove(&move_file);

		cout << "last move was: " << lastMove << endl;

		// if we made the last move, look for go file again
		if (lastMove.find(teamname) != string::npos){
			continue;
		}

		// remove opponent name
		opponentMove = lastMove.substr(lastMove.find(" ") + 1, lastMove.size());

		// play opponent move on board
		b.setPiece(opponentMove[0], opponentMove[2] - '0', b.opponentColor);
		cout << "board after opponent" << endl;
		cout << b.boardToStr() << endl;

		// make a move
		t = new Timer();
		t->start(); // start the timer
		ITL = 2;
		
		while(t->elapsedMilliseconds() <= timeLimit){
			Minimax m = Minimax(0.0, 0.0, b.ourColor, timeLimit);
			prevMoveToMake = m.minimaxSearch(&b, ITL, t);
			ITL += 2; // iterate by 2 ply 
			cout << prevMoveToMake << ", " << moveToMake << endl;
			if (!m.timeUp){
				moveToMake = prevMoveToMake;
			} else {
				cout << "time up, disregarding last minimax return" << endl;
			}
		}
		cout << "move we make actually " << prevMoveToMake << ", " << moveToMake << endl;

		//set piece for decided move
		b.setPiece(moveToMake, b.ourColor);
		cout << "new board: \n" << b.boardToStr() << endl << endl;

		// write move to move_file
		writeOurMove(&move_file, moveToMake);

		move_file.close();

		// loop again
	}
	return 0;
}
