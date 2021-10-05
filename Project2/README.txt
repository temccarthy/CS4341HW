Authors: Gabriel Dudlicek <grdudlicek@wpi.edu>, Tim McCarthy <temccarthy@wpi.edu>, Shawn Salvatto <swsalvatto@wpi.edu>
Date:   4 October 2021

AI Project 2: Othello Agent
Gabriel Dudlicek, Tim McCarthy, Shawn Salvatto
Description:
    This program serves as a player for a game of Othello played by another program. It will wait for a file teamname.go and in the absence of a end_game file, will read the 
opponent's move from move_file, generate it's of move, and write that move to more_file. 
    Our utility and evaluation functions return a value from 0 to 1 representing the percent utility values. Thus, our utility function can return three values: 0 for a loss, 0.5 
for a tie, and 1 for a win. This is calculated by counting the amount of discs for each team when there are no possible moves for either player. The evaluation function uses 
mobility, frontiers, and corners to calculate utility. Mobility is the number of potential moves, frontier discs are discs next to an open tile, and corners are the four corners 
of the board. Each of these are scaled: each mobility space is 0.05, each frontier is -0.05, and each corner is 0.2. These heuristics were based off of heuristics used by 
researchers at the University of Washington, Cornell, and Michael Buro and Kartik Kukreja. 
    To decide what branches to expand, we implemented alpha-beta pruning with iterative deepening search. We also explore positions from the inner parts of the board to the 
edges. A timer keeps track of how long the program has been running and terminates iterative-deepening search once 9.75 seconds has gone by to be sure our turn finishes inside the 10 
second time limit.

Results:
    For testing, we faced our program against human players, a random move player, and itself. We simply modified move_file manually to test against humans. Our program won 
easily for these tests. For a random move player, we had a simple program pick a legal move randomly. Our program easily beat this program as well. Lastly, we had our program 
face itself. These games were much closer, with the player who goes second being the winner.
    Our program does have a couple of weaknesses. Firstly, we did not implement any opening book moves. This would help improve our early gameplay and set us up for a later 
victory. Secondly, we were unable to implement machine learning, so our program will not learn from the games it plays. Lastly, we did not implement a stable discs function, 
which would add weight to the evaluation function for discs that are considered stable or semi-stable.
    We believe our program has a strong evaluation function and good heuristics. Because we use C++, our program runs significantly faster than Python programs. Combined with 
iterative deepening and alpha-beta pruning, we are able to calculate roughly 8 moves into the future. Our evaluation function also notes the most important strategies used by 
professional human players. Typically, pros will try to maximize mobility and minimize frontiers. This combined with our detection for corners, perhaps the greatest game-
indicator, explains why our program was able to easily defeat human and random opponents.

Contributions:
    Gabriel, Tim, and Shawn each contributed equal portions to this project and much of the code was written using peer programming. Gabriel worked mostly on the Board class and 
evaluation functions as well as the iterative deepening search. Tim worked primarily on minimax search and teamname.cpp. Shawn worked mostly on the iterative deepening search, 
the timer, and communication with the referee.

Prerequisites:
    * C++  10.3.0 or later
    * g++ 10.3.0 or later
    * Visual Studio Code

Compiling:
    Follow this tutorial to set up C++ and a compiler for Visual Studio Code: https://code.visualstudio.com/docs/languages/cpp
    Compile using the method in the example program of the tutorial.
    
Usage:
    ./teamname.cpp
