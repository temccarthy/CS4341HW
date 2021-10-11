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



string teamname = "teamname"; //possible name Takahashi - 2019 world champion 

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

//returns the corrent color based on move order
char determineOurColor(fstream* fin) {
	string firstLine;

	if (fin->peek() == EOF) {
		return 'b'; // there's a move already so we go second so we're orange
	} else {
		return 'o'; // there's no moves in move_file so we go first so we're blue
	}
}

//Writes our move to move_file
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
	bool playing = true;
	bool ourColorDetermined = false;

	Board b = Board();
	fstream move_file;
	string lastMove, opponentMove;
	int moveToMake, prevMoveToMake;
	int timeLimit = 9500; // 9500 milliseconds
	int ITL;
	Timer* t, *stopTimer;

	while (playing) {
		// start by looking for name.go file
		while (!goFileExists()) {
			// spin while waiting
		}

		cout << "go file found; opening move_file" << endl;

		// open move_file and read last line
		move_file.open("move_file", ios::in | ios::app);

		// determine which color we are (only occurs once)
		if (!ourColorDetermined) {
			char ourCol = determineOurColor(&move_file);
			cout << "setting our color: " << ourCol << endl;
			b.setOurColor(ourCol);
			ourColorDetermined = true;
		}

		lastMove = readLastMove(&move_file);

		cout << "last move was: " << lastMove << endl;

		// play opponent move on board (only if they didn't pass)
		if (lastMove != ""){
			opponentMove = lastMove.substr(lastMove.find(" ") + 1, lastMove.size());
			b.setPiece(opponentMove[0], opponentMove[2] - '0', b.opponentColor);
		}
		
		cout << "board after last move:" << endl;
		cout << b.boardToStr() << endl;

		// detect if gameOver
		if (b.isGameOver()) {
			cout << "GAME OVER" << endl;
			break;
		}
		

		// detect if we need to pass
		if (b.mobility(b.ourColor) == 0) {
			cout << "PASS" << endl;
			continue;
		} 

		//MINIMAX STARTS HERE
		// reset and start timer
		t = new Timer();
		t->start();
		ITL = 2;
		while(t->elapsedMilliseconds() < timeLimit){
			Minimax m = Minimax(timeLimit);
			
			
			int remainingMoves = 0;
			for (int row=0; row<8; row++){
				for (int col=0; col<8; col++){
					if (b.getPiece(row, col)==0){
						remainingMoves++;
					}
				}
			}
			if (remainingMoves<=ITL){
				for (int row=0; row<8; row++){
					for (int col=0; col<8; col++){
						if (b.flippedPieces(row, col, b.ourColor).size() > 0){
							moveToMake = b.getPieceNumFromCoords(row, col);
						}
					}
				}				
				continue;
			}else{
				prevMoveToMake = m.minimaxSearch(&b, ITL, t);
			}

			if (!m.timeUp){
				moveToMake = prevMoveToMake;
				cout << "Eval completed at iterative limit: " << ITL << endl;
				cout << "Move decided: " << moveToMake << "\n\n";
			}

			if (ITL > 60) {
				break;
			}

			ITL += 2; // iterate depth limit by 2 ply 
		}
		t->stop();
		//END MINIMAX
		cout << "total time taken to make move (ms): " << t->elapsedMilliseconds() << endl;
		cout << "final minimax decided move: " << moveToMake << endl;
		cout << "Board evaluation: " << b.evaluate() << endl;

		//set piece for decided move
		b.setPiece(moveToMake, b.ourColor);
		cout << "board after our move: \n" << b.boardToStr() << endl << endl;

		// write move to move_file
		writeOurMove(&move_file, moveToMake);

		move_file.close(); // close the file for other team to read

		stopTimer = new Timer();
		stopTimer->start();
		while (stopTimer->elapsedMilliseconds() < 500){ // wait .5 seconds before checking for move_file again
			// loop while waiting for go file to disappear
		}
		stopTimer->stop();

		// make move again
	}
	return 0;
}
