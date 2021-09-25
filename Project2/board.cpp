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
    bool * getFlipped(int row, int col, char color, bool potentialFlipped[64]);
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

	for (int i = 0; i < 64; i++) {
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
		
	}

	board[row * 8 + col] = color;
	return false;
}

bool * Board::getFlipped(int row, int col, char color, bool captured[64]){
    
    for(int* dir : directions) { // iterate through all directions
        int rowCurr = row;
        int colCurr = col;        
        bool potentialFlippedExists = false;
        bool legalMove = false;
        int i = 0;
        bool potentialFlipped[64];
        while (!outOfBounds(rowCurr, colCurr)) {
            rowCurr += dir[0];
            colCurr += dir[1];
        
            char colorCurr = getPiece(rowCurr, colCurr);
            if (colorCurr == '0') {
                break;
            } else if (colorCurr = color && potentialFlippedExists){
                legalMove = true; 
                break;   
            } else {
                potentialFlipped[i] = true;
                potentialFlippedExists = true;
            }
        }
        i++;
    }
    return captured;
}



string Board::boardToStr() {
	string output("");
	for (int i = 7; i > -1; i--) {
		for (int j = 0; j < 8; j++) {
			output += getPiece(i, j);
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
	// cases &= setPiece(1, 3, 'b'); // not true

	if (cases)
		cout << "all tests pass!" << endl;
	else
		cout << "tests fail" << endl;



	cout << endl << "board after tests" << endl;
	cout << boardToStr() << endl;
}

int main() {
	Board b = Board('b');

	cout << "starting board" << endl;
	cout << b.boardToStr() << endl;
	cout << "~~~~" << endl;

    bool *result;

    bool potentialFlipped[64] = {false};

    result = b.getFlipped(6, 1, 'o', potentialFlipped);

    int count = 0;
    
     for (int x = 0; x<64; x++){  //Displays the values  "0|1|1|0|1|1|1|0|" (What they become)
        cout << result[x] << '|';
        if(8%x == 0) cout << '\n';
    }
   cout << count;
	//b.testCases();

	return 0;
}

