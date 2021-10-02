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
	}

	return prevLine;
}

char determineOurColor(fstream* fin) {
	string firstLine;

	fin->seekg(0, fin->beg);
	if (getline(*fin, firstLine)) {
		return 'o'; // there's a move already so we go second so we're orange
	} else {
		return 'b'; // there's no moves in move_file so we go first so we're blue
	}
}

void writeOurMove(fstream* fin, int move) { // TODO: UNTESTED
	char col = 65 + move%8;
	char row = 31 + move/8;
	string moveString = teamname + " " + col + " " + row;
	*fin << moveString << endl;
}

int main() {

	Board testBoard = Board();
	testBoard.setOurColor('o');
	testBoard.setPiece('C', 5, 'b'); // otherteam
	// testBoard.setPiece(26, 'b'); // 2,1
	cout << "test board:" << endl;
	cout << testBoard.boardToStr() << endl;

	bool playing = false;
	bool ourColorDetermined = false;

	Board b = Board();

	fstream move_file;
	string lastMove, opponentMove;
	int moveToMake;
	Minimax m = Minimax(0.0,0.0);

	while (playing) {
		// start by looking for name.go file
		while (!goFileExists()) {
			// spin while waiting
		}
		playing = false; // TODO: remove this later; test that multiple moves in a row works

		cout << "go file found; opening move_file" << endl;

		// open move_file and read last line
		move_file.open("move_file");
		lastMove = readLastMove(&move_file);
		if (!ourColorDetermined) {
			char ourCol = determineOurColor(&move_file);
			cout << "our color: " << ourCol << endl;
			b.setOurColor(ourCol);
			ourColorDetermined = true;
		} // TODO: if other player goes first, make their move, otherwise skip that part

		move_file.close();

		cout << "last move was: " << lastMove << endl;

		// if we made the last move, look for go file again
		if (lastMove.find(teamname) != string::npos){
			continue;
		}

		// remove opponent name
		opponentMove = lastMove.substr(lastMove.find(" ") + 1, lastMove.size());
		// play opponent move on board
		// still need to translate from "B 3" to 2, 3
		// cout << opponentMove[0] << opponentMove[2] << endl;
		b.setPiece(opponentMove[0], opponentMove[2] - '0', b.opponentColor);
		cout << "board after opponent" << endl;
		cout << b.boardToStr() << endl;

		// make a move
		moveToMake = m.minimaxSearch(&b);
		cout << "move to make: " << moveToMake << endl;
		b.setPiece(moveToMake, b.ourColor);
		cout << "new board: \n" << b.boardToStr() << endl << endl;

		// write move to move_file
		writeOurMove(&move_file, moveToMake);

		// loop
	}

	// start by looking for name.go file
	// wait otherwise
	// when team.go exists, read move_file
	// if other team didn't make a move: close and wait
	// if other team made a move:
	// parse new info from move_file and update board
	// make move (within 10 sec)
	// append move to move_file
	// wait again and repeat

	return 0;
}
