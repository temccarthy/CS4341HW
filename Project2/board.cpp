using namespace std;
#include <iostream>
#include <string.h>
#include <vector>

class Board {
	char board[64];
	

public:
	Board(char ourColor);
	char getPiece(int row, int col);
	bool setPiece(int row, int col, char color);
	vector<int> flippedPieces(int row, int col, char color);
	string boardToStr();
	int getPieceNumFromCoords(int row, int col);
	
	void testCases();
private:
};

bool outOfBounds(int row, int col) {
	return (row < 0) || (row > 7) || (col < 0) || (col > 7);
}

// we don't do anything with ourColor?
Board::Board(char ourColor) {
	memset(board, 0, sizeof(board));

	board[27] = 'b'; //3,3
	board[28] = 'o'; //3,4
	board[35] = 'o'; //4,3
	board[36] = 'b'; //4,4
}

char Board::getPiece(int row, int col) {
	//get the piece from the coordinates passed in
	return board[row * 8 + col];
}

int Board::getPieceNumFromCoords(int row, int col) {
	return row * 8 + col;
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
			} else {
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

string Board::boardToStr() {
	string output("");
	for (int i = 7; i > -1; i--) {
		for (int j = 0; j < 8; j++) {
			if (getPiece(i, j) == 0) {
				output += "0";
			} else {
				output += getPiece(i, j);
			}
			output += "|";
		}
		output += '\n';
	}
	return output;
}

void Board::testCases() {
	bool cases = true;

	cases &= !setPiece(1, 1, 'o'); // false
	cases &= !setPiece(1, 1, 'b'); // false
	cases &= setPiece(2, 3, 'o'); // true
	cases &= !setPiece(1, 3, 'b'); // false
	cases &= setPiece(2, 2, 'b'); // true

	if (cases)
		cout << "all tests pass!" << endl;
	else
		cout << "tests fail" << endl;

	cout << endl << "board after tests" << endl;
	cout << boardToStr() << endl;
	cout << "test" << endl;
}

int main() {
	Board b = Board('b');

//	cout << "starting board" << endl;
//	cout << b.boardToStr() << endl;
//	cout << "~~~~" << endl;
	b.testCases();

	return 0;
}

