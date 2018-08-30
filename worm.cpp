//Author:Deahja Powell
//File: worm.cpp
//Description: This file contains the circular queue to hold the body of the worm
#include <iostream>
#include "worm.hpp"

WormBodQueue::WormBodQueue(int row, int col)
{
  MAX = (row-2) * (col-2);
  head = 0;
  tail = 0;
  worm = new Coord[MAX];
  count = 0;
  growCount = 0;
  isGrow = false;
}

int WormBodQueue::size() //size of circular queue
{
  if(head > tail)
    return head - tail + 1;
  else
    return MAX - tail + head + 1; 
}

//keeps track of elements of worm //insert
bool WormBodQueue::addBod(int row, int col) //push
{
   bool result = false;
  if(count < MAX)
    {
      worm[head].x = row;
      worm[head].y = col;
      //switched this
      head = (head + 1) % MAX;
      count++;
      result = true;
    }
  return result;
}

bool WormBodQueue::remove()//pop
{
  head = (head +1) % MAX;
  count --;
  return true;
}

Coord WormBodQueue::moveWorm(int wormX, int wormY)
{
  growing.x = -1;
  growing.y = -1;
  worm[head].x = wormX;
  worm[head].y = wormY;
  head++;
  if(head >= MAX)
    head = 0;
  if(growCount == 0)
    {
      isGrow = false;
      if(tail >= MAX)
	tail = 0;
      return worm[tail++];
    }
  else
    growCount--;
  return growing;
}

void WormBodQueue::growth(int munchieNum)
{
  growCount += munchieNum;
  isGrow = true;
}

bool WormBodQueue::isGrowing()
{
  return isGrow;
}
