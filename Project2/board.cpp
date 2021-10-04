using namespace std;

#include <iostream>
#include <string.h>
#include <vector>
#include "board.hpp"

// we don't do anything with ourColor?
Board::Board() {
	memset(board, 0, sizeof(board));

	board[27] = 'b'; //3,3
	board[28] = 'o'; //3,4
	board[35] = 'o'; //4,3
	board[36] = 'b'; //4,4
}

void Board::setOurColor(char color) {
	ourColor = color;
	if (color == 'o') {
		opponentColor = 'b';
	} else {
		opponentColor = 'o';
	}
}

bool outOfBounds(int row, int col) {
	return (row < 0) || (row > 7) || (col < 0) || (col > 7);
}

char Board::getPiece(int row, int col) {
	//get the piece from the coordinates passed in
	return board[row * 8 + col];
}

int Board::getPieceNumFromCoords(int row, int col) {
	return row * 8 + col;
}

Board* Board::copyBoard() {
	Board* newBoard = (Board*) malloc(sizeof(Board));
	memcpy(newBoard, board, sizeof(Board));
	return newBoard;
}

// only for reading from textfile
bool Board::setPiece(char col, int row, char color) {
	return setPiece(row-1, col-65, color);
}

bool Board::setPiece(int boardPos, char color) {
	return setPiece(boardPos/8, boardPos%8, color);
}

bool Board::setPiece(int row, int col, char color) {
	vector<int> flipped = flippedPieces(row, col, color);

	if (!outOfBounds(row, col) && getPiece(row, col)==0 && flipped.size()>0) { // if inbounds and space empty	
		for (int pieceNum: flipped){
			board[pieceNum] = color;
		}
		int pieceNum = getPieceNumFromCoords(row, col);
		board[pieceNum] = color;
		return true;
	}else{
		return false;
	}
}

vector<int> Board::flippedPieces(int row, int col, char color){
	int directions[8][2] = { { -1, 0 }, { -1, -1 }, { -1, 1 }, { 1, 0 },
			{ 1, -1 }, { 1, 1 }, { 0, -1 }, { 0, 1 } };
	
	vector<int> flipped;

	if (getPiece(row, col) != 0){
		return flipped;
	}

	for(int* dir : directions) { // iterate through all directions
		int rowCurr = row;
		int colCurr = col;
		bool legalMove = false;
		vector<int> potentialFlipped;
		
		while (!outOfBounds(rowCurr, colCurr)) {
			rowCurr += dir[0];
			colCurr += dir[1];
		
			char colorCurr = getPiece(rowCurr, colCurr);
			if (colorCurr == 0) {
				break;
			} else if (colorCurr==color && potentialFlipped.size()>0) {
				legalMove = true;
				break;	
			} else if(colorCurr != color) {
				int pieceNum = getPieceNumFromCoords(rowCurr, colCurr);
				potentialFlipped.push_back(pieceNum);
			}
		}

		if (legalMove){
			flipped.reserve(flipped.size() + distance(potentialFlipped.begin(),potentialFlipped.end()));
			flipped.insert(flipped.end(),potentialFlipped.begin(),potentialFlipped.end());
		}
	}

	return flipped;
}

bool Board::isGameOver() {
	for (int row=0; row<8; row++){
		for (int col=0; col<8; col++){
			if ((flippedPieces(row, col, 'o').size() + flippedPieces(row, col, 'b').size()) > 0){
				return false;
			}
		}
	}
	return true;
}

float Board::utility() {
	int blue, orange = 0;
	for (int i = 0; i < 64; i++) {
		if (board[i] == 'b'){
			blue++;
		} else if (board[i] == 'o') {
			orange++;
		}
	}

	if (blue == orange) {
		return 0.5;
	} else if ((ourColor == 'b' && blue > orange)||(ourColor == 'o' && blue < orange)) {
		return 1;
	} else {
		return 0;
	}
}


//calculates the total number of legal moves across the board for a color - flipping fewer pieces is better
int Board::mobility(){
	int legalMoves = 0;

	for (int row=0; row<8; row++){
		for (int col=0; col<8; col++){
			if (flippedPieces(row, col, ourColor).size() > 0){
				legalMoves++;
			}
		}
	}
	
	return legalMoves;
}

//calculates the number of stable pieces
//currently only counts the number of held corner pieces
//TODO: calculate all stable pieces
int Board::numberOfStableDiscs(){
	//corner piece numner 0, 7, 56, 63

	int heldStablePieces = 0;

	if(getPiece(0,0) == ourColor) heldStablePieces++;
	if(getPiece(0,0) == ourColor) heldStablePieces++;
	if(getPiece(0,0) == ourColor) heldStablePieces++;
	if(getPiece(0,0) == ourColor) heldStablePieces++; 

	return heldStablePieces;
}

// TODO: finish eval fcn
float Board::evaluate() {
	int blue, orange = 1;

	int legalMoves = mobility();

	return blue;
}


string Board::boardToStr() {
	string output("");
	for (int i = 7; i > -1; i--) {
		for (int j = 0; j < 8; j++) {
			if (getPiece(i, j) == 0) {
				output += " ";
			} else {
				output += getPiece(i, j);
			}
			output += "|";
		}
		output += "|\n";
	}
	return output;
}

void Board::testCases() {
	Board* boardCopy = copyBoard();
	bool cases = true;

	cases &= !boardCopy->setPiece(1, 1, 'o'); // false
	cases &= !boardCopy->setPiece(1, 1, 'b'); // false
	cases &= boardCopy->setPiece(2, 3, 'o'); // true
	cases &= !boardCopy->setPiece(1, 3, 'b'); // false
	cases &= boardCopy->setPiece(2, 2, 'b'); // true

	if (cases)
		cout << "all tests pass!" << endl;
	else
		cout << "tests fail" << endl;

	cout << endl << "board after tests" << endl;
	cout << boardCopy->boardToStr() << endl;
	cout << "test" << endl;
}
