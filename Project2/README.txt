Authors: Gabriel Dudlicek <grdudlicek@wpi.edu>, Tim McCarthy <temccarthy@wpi.edu>, Shawn Salvatto <swsalvatto@wpi.edu>
Date:   4 October 2021

Description:
    This program serves as a player for a game of Othello played another program. It will wait for a file teamname.go and in the abscence of a end_game file, will read the opponent's move from move_file, generate it's of move, and write that move to more_file. Our utility and evaluation functions return a value from 0 to 1 representing the percent utility values. Thus, our utility function can return three values: 0 for a loss, 0.5 for a tie, and 1 for a win. This is calculated by counting the amount of discs for each team when there are no possible moves for either player. 

Prerequisites:
    * C++  10.3.0 or later
    * g++ 10.3.0 or later
    * Visual Studio Code

Compiling:
    Follow this tutorial to set up C++ and a compiler for Visual Studio Code: https://code.visualstudio.com/docs/languages/cpp
    
Usage:
    ./teamname.cpp
