using namespace std;

#include <iostream>
#include <string.h>

class Board {
    char board[8][8];
    int* No8(int x, int y);
    public:
        Board(char ourColor);
        int* getLegalMoves();
        string boardToStr();
};

Board::Board(char ourColor) {
    memset(board, 0, sizeof(board));

    // DOUBLE CHECK COLORS are CORRECT
    if (ourColor == 'b'){ // we go first
        board[3][3]='b';
        board[4][3]='o';
        board[3][4]='o';
        board[4][4]='b';
    } else { // we go second
        board[3][3]='o';
        board[4][3]='b';
        board[3][4]='b';
        board[4][4]='o';
    }
    // now we're always blue (I think)
}

// neighbors fcn
int* Board::No8(int x, int y){
    // implement getting neighbors
    //
}

// get neighbor in a direction

int* Board::getLegalMoves() {
    // so copy the referee

    // iterate through each spot, looking for empty
    for (int i=0; i<8; i++){
        for (int j=0; j<8; j++){
            // if empty, look for 1 or more oranges in a row
                // then look for a blue at the end --> return that place as a legal move
        }
    }
    // if yes return
}



string Board::boardToStr(){
    string output("");
    for (int i=0; i<8; i++){
        for (int j=0; j<8; j++){
            if (board[i][j] == 0) output+=" ";
            else output += board[i][j];
        }
        output += '\n';
    }
    return output;
}


int main() {
    Board b = Board('b');
    cout << b.boardToStr() << endl;

    return 0;
}
