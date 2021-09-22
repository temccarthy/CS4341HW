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

int main() {
	bool playing = true;
	Board b = Board('b');

	fstream move_file;
	string lastMove, opponentMove;

	while (playing) {
		// start by looking for name.go file
		while (!goFileExists()) {
			// spin while waiting
		}
		playing = false; // DEBUG

		cout << "go file found; opening move_file" << endl;

		// open move_file and read last line
		move_file.open("move_file");
		lastMove = readLastMove(&move_file);

		cout << "last move was: " << lastMove << endl;

		// if we made the last move, look for go file again
		if (lastMove.find(teamname) != string::npos){
			continue;
		}

		// remove opponent name
		opponentMove = lastMove.substr(lastMove.find(" ") + 1, lastMove.size()); // UNTESTED
		cout << opponentMove << endl;
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
