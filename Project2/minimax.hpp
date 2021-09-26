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

public:
	int minimaxSearch(Board* board);
private:
	UtilityMovePair* maxValue(Board* board);
	UtilityMovePair* minValue(Board* board);
};



#endif /* MINIMAX_HPP_ */
