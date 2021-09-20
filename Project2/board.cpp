using namespace std;

#include <iostream>
#include <string.h>

class Board {
    char board[64];
    int directions[8][2] = {{-1,0},{-1,-1},{-1,1},{1,0},{1,-1},{1,1},{0,-1},{0,1}};

    public:
        Board(char ourColor);
        char getPiece(int row, int col);
        bool setPiece(int row, int col, char color);
        string boardToStr();
        int getPieceNumFromCoords(int row, int col);
};

bool outOfBounds(int row, int col){
    return (row < 0) || (row > 7) || (col < 0) || (col > 7);
}

Board::Board(char ourColor) {
    memset(board, 0, sizeof(board));

        for (int i = 0; i < sizeof(board); i++) {
            board[i] = '0';
        }   

        board[27]= 'o';
        board[28]= 'b';
        board[35]= 'b';   
        board[36]= 'o';
}

char Board::getPiece(int row, int col){
    //get the piece from the coordinates passed in
    return board[row * 8 + col];
}

int Board::getPieceNumFromCoords(int row, int col){
    return row * 8 + col;
}

bool Board::setPiece(int row, int col, char color){
    
//     if (!outOfBounds(row, col) && !getPiece(row, col)=='0' ){
//         for(int[] dir : directions){
//             int rowCurr = row;
//             int colCurr = col;
//             bool potentialFlipped[64];
//             bool legalMove = false;
//             while (!outOfBounds(rowCurr, colCurr))
//             {
//                 rowCurr += dir[0];
//                 colCurr += dir[1];
//             }
//             char colorCurr = getPiece(rowCurr, colCurr);
//             if (colorCurr = '0'){
//                 break;
//             }else if (colorCurr = color)
//             {
//                 for (bool potentialFlip : potentialFlipped){
//                     if (potentialFlip){
//                         legalMove = true;
//                     }
//                 }
//             }
            
//         }
//     }

//     board[row * 8 + col] = color;
    return false;
}

string Board::boardToStr(){
    string output("");
    for (int i=0; i<8; i++){
        for (int j=0; j<8; j++){
            output += getPiece(i, j);
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
