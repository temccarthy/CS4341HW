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
};

class Minimax {
	float alpha, beta;
	char ourColor,opponentColor;
	int iterativeLimit;
	int ply;

public:
	Minimax(float a, float b, char color);
	int minimaxSearch(Board* board);
private:
	UtilityMovePair* maxValue(Board* board, int moveToMake);
	UtilityMovePair* minValue(Board* board, int moveToMake);
};



#endif /* MINIMAX_HPP_ */
