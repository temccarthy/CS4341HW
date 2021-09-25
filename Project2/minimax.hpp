/*
 * minimax.hpp
 *
 *  Created on: Sep 25, 2021
 *      Author: tim
 */

#ifndef MINIMAX_HPP_
#define MINIMAX_HPP_

#include "board.hpp"

class Minimax {
	int alpha, beta;

public:
	int minimaxSearch(Board board);
private:
	int maxValue(Board board);
	int minValue(Board board);
};

#endif /* MINIMAX_HPP_ */
