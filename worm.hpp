//Author: Deahja Powell
//File: worm.hpp
//header file for circular que
#ifndef WORM_HPP
#define WORM_HPP

#include<iostream>
#include<queue>
#include "coord.hpp"

class WormBodQueue
{
  int MAX;
  int x, y;
  int row, col;
  int count;
  int growCount;
  Coord growing;
  bool isGrow;
public:
  WormBodQueue(int row, int col);  //creates the worm queue
  bool addBod(int row, int col);
  bool remove();
  int size();
  Coord moveWorm(int wormX, int wormY);
  //  int headX, headY, tailX, tailY;
  int head, tail;
  Coord * worm;
  void growth(int munchieNum);
  bool isGrowing();
};
#endif

