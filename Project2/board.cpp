using namespace std;

#include <iostream>
#include <string.h>

class Board {
	char board[64];
	int directions[8][2] = { { -1, 0 }, { -1, -1 }, { -1, 1 }, { 1, 0 },
			{ 1, -1 }, { 1, 1 }, { 0, -1 }, { 0, 1 } };

public:
	Board(char ourColor);
	char getPiece(int row, int col);
	bool setPiece(int row, int col, char color);
	string boardToStr();
	int getPieceNumFromCoords(int row, int col);
	void testCases();
private:
	;
};

bool outOfBounds(int row, int col) {
	return (row < 0) || (row > 7) || (col < 0) || (col > 7);
}

Board::Board(char ourColor) {
	memset(board, 0, sizeof(board));

	for (int i = 0; i < sizeof(board); i++) {
		board[i] = '0';
	}

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

	if (!outOfBounds(row, col) && getPiece(row, col) == 0) { // if inbounds and space empty
		for(int* dir : directions) {
			int rowCurr = row;
			int colCurr = col;

			bool potentialFlipped[64];
			bool legalMove = false;
			while (!outOfBounds(rowCurr, colCurr))
			{
				rowCurr += dir[0];
				colCurr += dir[1];
			}
			char colorCurr = getPiece(rowCurr, colCurr);
			if (colorCurr == 0) {
				break;
			} else if (colorCurr = color)
			{
				for (bool potentialFlip : potentialFlipped) {
					if (potentialFlip) {
						legalMove = true;
					}
				}
			}
		}
	}

	board[row * 8 + col] = color;
	return false;
}

string Board::boardToStr() {
	string output("");
	for (int i = 7; i > -1; i--) {
		for (int j = 0; j < 8; j++) {
			output += getPiece(i, j);
		}
		output += '\n';
	}
	return output;
}

void Board::testCases() {
	Board b = Board('b');
	bool cases = true;

	cases &= !setPiece(1, 1, 'o'); // false
	cases &= !setPiece(1, 1, 'b'); // false
	cases &= setPiece(2, 3, 'o'); // true
	// cases &= setPiece(1, 3, 'b'); // not true

	if (cases)
		cout << "all tests pass!" << endl;
	else
		cout << "tests fail" << endl;
}

int main() {
	Board b = Board('b');

	cout << "starting board" << endl;
	cout << b.boardToStr() << endl;
	cout << "~~~~" << endl;

	b.testCases();

	cout << "board after tests" << endl << endl;
	cout << b.boardToStr() << endl;

	return 0;
}

