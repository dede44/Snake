//Author: Deahja Powell
//File: gameBoard.hpp
//Header file for board class
#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP

#include <iostream>
#include "coord.hpp"
#include "worm.hpp"

class GameBoard
{
public:
  GameBoard(int row, int col); //constructor
  //  ~GameBoard();
  Coord munchieLoc();
  int munchieNum();
  int score;
  Coord * freePool;
  bool addFreePool(int x, int y);
  bool removeFreePool(int x, int y);
  void printScreen();
private:

  int ** gameBoard;
  int lastIdx;
  int * wormBod;
  int global_row;
  int global_col;

};

#endif
