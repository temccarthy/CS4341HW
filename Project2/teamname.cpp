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
#include "board.cpp"

string teamname = "teamname";

// from https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-14-17-c
inline bool goFileExists() {
	struct stat buffer;
	return (stat((teamname + ".go").c_str(), &buffer) == 0);
}

// from https://stackoverflow.com/questions/11876290/c-fastest-way-to-read-only-last-line-of-text-file
string readLastLine(fstream fin) {
	fin.seekg(-1, ios_base::end);           // go to one spot before the EOF

	bool keepLooping = true;
	while (keepLooping) {
		char ch;
		fin.get(ch);                        // Get current byte's data

		if ((int) fin.tellg() <= 1) { 		// If the data was at or before the 0th byte
			fin.seekg(0);                   // The first line is the last line
			keepLooping = false;            // So stop there
		} else if (ch == '\n') {            // If the data was a newline
			keepLooping = false;            // Stop at the current position.
		} else {          					// If the data was neither a newline nor at the 0 byte
			fin.seekg(-2, ios_base::cur); 	// Move to the front of that data, then to the front of the data before it
		}
	}

	string lastLine;
	getline(fin, lastLine);
	return lastLine;
}

int main() {
	bool playing = true;
	Board b = Board('b');

	fstream move_file;
	string lastMove, opponentMove;

	while (playing) {
		while (!goFileExists()) {} // spin while waiting

		// open move_file and read last line
		move_file.open("move_file");
		lastMove = readLastLine(move_file);

		// if we made the last move, continue
		if (lastMove.find(teamname, 0)) continue; // UNTESTED lol

		// remove opponent name
		opponentMove = lastMove.substr(lastMove.find(" ") + 1, lastMove.size()); // UNTESTED



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
