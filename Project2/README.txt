Authors: Gabriel Dudlicek <grdudlicek@wpi.edu>, Tim McCarthy <temccarthy@wpi.edu>, Shawn Salvatto <swsalvatto@wpi.edu>
Date:   4 October 2021

Description:
    This program serves as a player for a game of Othello played another program. It will wait for a file teamname.go and in the abscence of a end_game file, will read the 
opponent's move from move_file, generate it's of move, and write that move to more_file. 
    Our utility and evaluation functions return a value from 0 to 1 representing the percentutility values. Thus, our utility function can return three values: 0 for a loss, 0.5 
for a tie, and 1 for a win. This is calculated by counting the amount of discs for each team when there are no possible moves for either player. The evaluation function uses 
mobility, frontiers, and corners to calculate utility. Mobility is the number of potential moves, frontier discs are discs next to an open tile, and corners are the four corners 
of the board. Each of these are scaled: each mobility space is 0.05, each frontier is -0.05, and eah corner is 0.2. These heuristics were based off of heuristics used by 
reasearchers at the University of Washington, Cornell, and Michael Buro and Kartik Kukreja. 
    To decide what branches to expand, we implemented alpha-beta pruning. We also explore positions from the inner parts of the board to the edges.

Prerequisites:
    * C++  10.3.0 or later
    * g++ 10.3.0 or later
    * Visual Studio Code

Compiling:
    Follow this tutorial to set up C++ and a compiler for Visual Studio Code: https://code.visualstudio.com/docs/languages/cpp
    
Usage:
    ./teamname.cpp
