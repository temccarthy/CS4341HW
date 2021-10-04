using namespace std;

#include <iostream>
#include <string.h>
#include <vector>
#include "board.hpp"

//Board contructor
Board::Board() {
	memset(board, 0, sizeof(board));

	board[27] = 'b'; //3,3
	board[28] = 'o'; //3,4
	board[35] = 'o'; //4,3
	board[36] = 'b'; //4,4
}

//Sets our color to the correct one
void Board::setOurColor(char color) {
	ourColor = color;
	if (color == 'o') {
		opponentColor = 'b';
	} else {
		opponentColor = 'o';
	}
}

//Returns true if a coordinate is out of bounds
bool outOfBounds(int row, int col) {
	return (row < 0) || (row > 7) || (col < 0) || (col > 7);
}

//returns a board piece at a coordinate
char Board::getPiece(int row, int col) {
	//get the piece from the coordinates passed in
	return board[row * 8 + col];
}

//returns a board piece at a coordinate
int Board::getPieceNumFromCoords(int row, int col) {
	return row * 8 + col;
}

//Function for copying a board
Board* Board::copyBoard() {
	Board* newBoard = (Board*) malloc(sizeof(Board));
	memcpy(newBoard, board, sizeof(Board));
	return newBoard;
}

//Attempts to Set a piece on the board
//Returns true and updates the board if the move is valid
//only for reading from textfile
bool Board::setPiece(char col, int row, char color) {
	return setPiece(row-1, col-65, color);
}

//Attempts to Set a piece on the board
//Returns true and updates the board if the move is valid
bool Board::setPiece(int boardPos, char color) {
	return setPiece(boardPos/8, boardPos%8, color);
}

//Attempts to Set a piece on the board
//Returns true and updates the board if the move is valid
bool Board::setPiece(int row, int col, char color) {
	vector<int> flipped = flippedPieces(row, col, color);

	if (!outOfBounds(row, col) && getPiece(row, col)==0 && flipped.size()>0) { // if inbounds and space empty and will flip pieces - determining that a move is legal
		for (int pieceNum: flipped){
			board[pieceNum] = color;
		}
		int pieceNum = getPieceNumFromCoords(row, col);
		board[pieceNum] = color; //assigns the board piece to a certain color
		return true;
	}else{
		return false;
	}
}

//returns a vector of all pieces that will be flipped from a given movw
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
		
		while (!outOfBounds(rowCurr, colCurr)) { //while we are in bounds
			rowCurr += dir[0];
			colCurr += dir[1];
		
			char colorCurr = getPiece(rowCurr, colCurr);
			if (colorCurr == 0) { //break if the spot is empty
				break;
			} else if (colorCurr==color && potentialFlipped.size()>0) { //if the move is legal 
				legalMove = true;
				break;	
			} else if(colorCurr != color) { //if we are comparing two different colors
				int pieceNum = getPieceNumFromCoords(rowCurr, colCurr);
				potentialFlipped.push_back(pieceNum);
			}
		}

		if (legalMove){ //if the move is legal, flip the pieces on the board and add them to the return vector
			flipped.reserve(flipped.size() + distance(potentialFlipped.begin(),potentialFlipped.end()));
			flipped.insert(flipped.end(),potentialFlipped.begin(),potentialFlipped.end());
		}
	}

	return flipped;
}

//returns true if the game is over
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

//Returns the calculated utility of the current board
//Utility is only used to determine if we have won, lost, or tied the game
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
int Board::mobility(char color){
	int legalMoves = 0;

	for (int row=0; row<8; row++){
		for (int col=0; col<8; col++){
			if (flippedPieces(row, col, color).size() > 0){
				legalMoves++;
			}
		}
	}
	
	return legalMoves;
}

//calculates the number of stable pieces
//currently only counts the number of held corner pieces
//TODO: calculate all stable pieces
int Board::numStableDiscs(char color){
	//corner piece numner 0, 7, 56, 63

	int heldStablePieces = 0;

	if(getPiece(0,0) == ourColor) heldStablePieces++;
	if(getPiece(0,0) == ourColor) heldStablePieces++;
	if(getPiece(0,0) == ourColor) heldStablePieces++;
	if(getPiece(0,0) == ourColor) heldStablePieces++; 

	return heldStablePieces;
}

//Returns the number of corners held
int Board::numCorners(char color){

	int corners = 0;

	if(getPiece(0,0) == color) corners++;
	if(getPiece(0,7) == color) corners++;
	if(getPiece(7,0) == color) corners++;
	if(getPiece(7,7) == color) corners++; 

	return corners;
}

//returns the number of fronteir discs
//A frontier disc is one that lies next to an open tile
int Board::numFrontierDiscs(char color){
	int numFrontierDiscs = 0;
	int directions[8][2] = { { -1, 0 }, { -1, -1 }, { -1, 1 }, { 1, 0 },
			{ 1, -1 }, { 1, 1 }, { 0, -1 }, { 0, 1 } };

	for (int i = 7; i > -1; i--) {
		for (int j = 0; j < 8; j++) {
			char colorCurr = getPiece(i, j);
			if (color == colorCurr){
				for(int* dir : directions) { // iterate through all directions
				int rowCurr = i;
				int colCurr = j;		
				rowCurr += dir[0];
				colCurr += dir[1];
				if (!outOfBounds(rowCurr, colCurr)){
					char boarder = getPiece(rowCurr, colCurr);
					if (boarder==0) {
					numFrontierDiscs++;
					}
				}		
			}
			}
		}
	}
	return numFrontierDiscs;
}

//returns an evaluation of the current board
//combines all three evaluation heuristics to calculate eval score
float Board::evaluate(){
	int utility = 0;
	utility += (mobility(ourColor)-mobility(opponentColor))*0.05;
	utility += (numCorners(ourColor)-numCorners(opponentColor))*0.20;
	utility += (numFrontierDiscs(opponentColor)-numFrontierDiscs(ourColor)*0.05);

	return utility;
}

//returns the board represented in a string for sanity
string Board::boardToStr() {
	string output("");
	string nums = "12345678";
	for (int i = 7; i > -1; i--) {
		output += nums[i];
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
	cout << " A B C D E F G H\n";
	return output;
}

//Test cases for piece movement
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
