//Author: Deahja Powell
//File: screen.cpp
#include<curses.h>
#include "getChar.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include "gameBoard.hpp"
#include "worm.hpp"
#include "coord.hpp"

void startup( void );
void terminate( void );

int main(int argc, char **argv)
{
  //Error message if not passed right amount of variables
  if(argc != 3)
    {
      std::cout << "Invalid input: Needs executable, length, and width." << std::endl;
      return 1;
    }

  int row = atoi(argv[1]); 
  int col = atoi(argv[2]);

  //Error message if board doesn't stay in bounds
  if(row < 10 || row > 25)
    {
      std::cout << "Board is either too small or large." << std::endl;
      return 1; //stop script
    }

  if(col < 10 || col > 80)
    {
      std::cout << "Board is either to small or large." << std::endl;
      return 1; //stop script
    }

  startup(); //start game  
  //---------Constructors------------
  GameBoard board = GameBoard(row,col); //creates board
  WormBodQueue worm = WormBodQueue(row, col); //creates worm array //took away -2s

  int score = board.score;

  //create title & score
  move(0, 0);
  addstr("Worming Around!");
  move(0, col/1.2);
  printw("Score:  %d",score);
  
  //create side borders
  for(int i = 1; i < row; i++)
    {
      move(i, 0);
      addch('*');
      move(i, col);
      addch('*');	
    }
  //add top & bottom borders
  for(int i = 0; i < col + 1; i++)
    {
      move(1, i);
      addch('*');
      move(row, i);
      addch('*');
    }

  refresh();

  //-----------generate munchie -----------------
  int munchieNum = board.munchieNum();
  Coord munchieLoc = board.munchieLoc();
  char munchieChar = '0' + munchieNum;
  
  //Output munchie
  move(munchieLoc.x+1, munchieLoc.y);
  addch(munchieChar);
  refresh();

  bool failed;
  //worm head & tail at start
  int wormX = row/2;
  int wormY = (col/2);
  // mvaddch(wormX+1, wormY, '@');
  //worm.addBod(wormX, wormY);
  //failed = board.removeFreePool(wormX, wormY);

  for(int i = 0; i < 8; i++)
    {
      mvaddch(wormX+1, wormY+i-4, 'o');
      worm.addBod(wormX, wormY+i-4); 
      failed = board.removeFreePool(wormX, wormY+i-4);
    }
  wormY = (col/2) + 3;
  mvaddch(wormX+1, wormY, '@');  
  refresh();

  int pwormX;
  int pwormY;

  Coord tail;
  bool playing = 1; 

  //  ----------Move the snake ------------------
  while(playing) 
    {
      char c = get_char();
      bool notCase = false;
      pwormX = wormX;
      pwormY = wormY;
      switch(c)
	{
	case 'k': //move up
	  wormX -= 1; 
	  notCase = true;
	  refresh();
	  break;
	case 'j': //move down
	  wormX += 1;
	  notCase = true;
	  refresh();
	  break;
	case 'h': //move left
	  wormY -= 1;
	  notCase = true;
	  refresh();
	  break;
	case 'l': //move right
	  wormY +=1;
	  notCase = true;
	  refresh(); 
	  break;
	case 'q': //quit game
	  playing = 0;
	default:
	  break;
	}
      if(notCase == true)
	{      
	  mvaddch(wormX+1, wormY, '@');
	  mvaddch(pwormX+1, pwormY, 'o');

	  tail = worm.moveWorm(wormX, wormY);
	  failed = board.removeFreePool(wormX, wormY);
	  
	  if(failed == false)
	    playing = 0;
	  
	  if(tail.x != -1& tail.y != -1)
	    {
	      mvaddch(tail.x+1, tail.y, ' ');
	      board.addFreePool(tail.x,tail.y);
	    }
	  
	  //regenerate a munchie if eaten 
	  if(wormX == munchieLoc.x && wormY == munchieLoc.y)
	    {
	      score += munchieNum; //update score
	      worm.growth(munchieNum);
	      munchieNum = board.munchieNum(); 
	      munchieLoc = board.munchieLoc();
	      munchieChar = '0' + munchieNum;
	      mvaddch(munchieLoc.x+1, munchieLoc.y, munchieChar);
	    }
	  
	  //testing board
	  board.printScreen();
	  
	  refresh();
	  //Updates score
	  move(0, col-4);
	  move(0, col/1.2);
	  printw("Score:  %d",score);
	  refresh();
	}
    }  
  
  terminate();
}

void startup( void )
{
  initscr();	    /* activate curses    */
  curs_set(0);   /* prevent the cursor to be displayed     */
  clear();	    /* clear the screen that curses provides  */           
  noecho();	    /* prevent the input chars to be echoed to the screen   */      
  cbreak();	    /* change the stty so that characters are delivered to the
		       program as they are typed--no need to hit the return key!  */
}

void terminate( void )
{
  mvcur( 0, COLS - 1, LINES - 1, 0 );
  clear();
  refresh();
  endwin();
}

