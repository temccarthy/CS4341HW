/*
 * minimax.hpp
 *
 *  Created on: Sep 25, 2021
 *      Author: tim
 */

#ifndef MINIMAX_HPP_
#define MINIMAX_HPP_

using namespace std;
#include "board.hpp"

struct UtilityMovePair {
	int move;
	float utility;
	UtilityMovePair(int m, float u) {
		move = m;
		utility = u;
	}

	bool equals(UtilityMovePair* newPair){
		return (move == newPair->move && utility == newPair->utility);
	}
	
};

class Minimax {
	float alpha, beta;
	bool hitITL;

	// order to check moves in, instead of just checking 1, 2, 3, 4 etc
	// it goes in a spiral from the middle out
	int moveOrder[64] = {27, 28, 36, 35, 34, 26, 18, 19,
					  20, 21, 29, 37, 45, 44, 43, 42,
					  41, 33, 25, 17, 9, 10, 11, 12,
					  13, 14, 22, 30, 38, 46, 54, 53,
					  52, 51, 50, 49, 48, 40, 32, 24,
					  16, 8, 0, 1, 2, 3, 4, 5,
					  6, 7, 15, 23, 31, 39, 47, 55,
					  63, 62, 61, 60, 59, 58, 57, 56};
	char ourColor,opponentColor;
	//int iterativeLimit = 1;

public:
	Minimax(float a, float b, char color);
	int minimaxSearch(Board* board);
private:
	UtilityMovePair* maxValue(Board* board, int moveToMake, int ply, int ITL);
	UtilityMovePair* minValue(Board* board, int moveToMake, int ply, int ITL);
	void setITL(bool val);
	bool getITL();
};



#endif /* MINIMAX_HPP_ */


/*
Python code for generating moveOrder

a = 27
l = []
multiplier = 1
lambdas = [lambda x: x+(1),
lambda x: x+(8),
lambda x: x-(1),
lambda x: x-(8)]
lambda_ctr = 0

l.append(a)
while True:
    for i in range(multiplier):
        a = lambdas[lambda_ctr](a)
        l.append(a)
    lambda_ctr = (lambda_ctr + 1) % 4
    if lambda_ctr % 2 == 0:
        multiplier += 1

    if len(l) >= 64:
        break

print(l[:64])
 */
