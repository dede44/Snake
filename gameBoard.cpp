//Author:Deahja Powell
//File: gameBoard.cpp
#include<iostream>
#include<fstream>
#include<ostream>
#include "gameBoard.hpp"
#include <cstdlib>
#include <iomanip>
#include<curses.h>

GameBoard::GameBoard(int row, int col)
{
  score = 0;
  int x, y;
  int SIZE = (row-2) * (col-2);
  lastIdx = 0; //numbers that go in space 
  global_row = row;
  global_col = col;
  
  //Make board with coordinates
  freePool = new Coord [SIZE];

  //create board as 2D array
  gameBoard =  new  int *[row];
  for(int i = 0; i < row; i++)
    gameBoard[i] = new int[col];

  //Loop to add numbers & coords in space
  for(int i = 1; i < row-1 ; i++)
    {
      for(int j = 1; j < col-1; j++)
	{
	  gameBoard[i][j] = lastIdx;
	  freePool[lastIdx].x = i;
	  freePool[lastIdx].y = j;
	  lastIdx++;
	}
    }

  //add the -1 for top & bottom walls 
  for(int i = 0; i < col; i++)
    {
      gameBoard[0][i] = -1;
      gameBoard[row-1][i] = -1;
    } 

  //add the -1 for side walls  
  for(int i = 0; i < row; i++)
    {
      gameBoard[i][0] = -1;
      gameBoard[i][col-1] = -1;
      }
}

/*
GameBoard::~GameBoard() //destructor
{
  delete [] freePool;
  for(int i = 0; i < global_row; i++)
    delete [] gameBoard[i];
  delete [] gameBoard;
}
*/
Coord GameBoard::munchieLoc()
{
  //generate random number for location index in freepool array
  srand(time(NULL));
  int space = rand() % lastIdx;
  return freePool[space];
}

int GameBoard::munchieNum()
{
  srand(time(NULL));
  int munchieNum = rand() % 9 + 1;
  return munchieNum;
}

bool GameBoard::addFreePool(int x, int y)
{
  if(gameBoard[x][y] == -1)
    {
      freePool[lastIdx].x = x;
      freePool[lastIdx].y = y;
      gameBoard[x][y] = lastIdx;
      lastIdx++;
      return true;
    }
  return false;
}

bool GameBoard::removeFreePool(int x, int y)
{
  if(gameBoard[x][y] != -1)
    {
      lastIdx--;
      int space = gameBoard[x][y];
      freePool[space].x = freePool[lastIdx].x;
      freePool[space].y = freePool[lastIdx].y;
      gameBoard[freePool[space].x][freePool[space].y] = space;
      gameBoard[x][y] = -1;
      return true;
    }
  return false;
}

void GameBoard::printScreen()
{

  std::fstream fs;
  fs.open("print_screen.txt", std::fstream::out);
  fs << "rows: " << global_row;
  fs << "cols: " << global_col << std::endl;
  for(int i = 0; i < global_row; i++)
    {
      for(int j = 0; j < global_col; j++)
      {
	fs << std::setw(4) << gameBoard[i][j] << std::flush;
      }
      fs << std::endl;
    }
}
