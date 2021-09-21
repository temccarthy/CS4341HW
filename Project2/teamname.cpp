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
#include "board.cpp"

string teamname = "teamname";

// from https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-14-17-c
inline bool goFileExists(){
	struct stat buffer;
	return (stat ((teamname+".go").c_str(), &buffer) == 0);
}

int main() {
	bool playing = true;
	Board b = Board('b');

	while (playing) {
		while (!goFileExists()) {} // spin while waiting

		// open move_file
		// if we made the last move, continue

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
