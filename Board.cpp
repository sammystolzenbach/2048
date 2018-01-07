/***************** 
* Sammy Stolzenbach
* COMP11
* HW7
* 2048 Board.cpp
******************/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Board.h"

using namespace std;

//default constructor 
Board::Board()
{
  board = NULL;//gameboard
  dimen = 0;
  first_tiles = true;//bool set to false after first tiles placed
  tempboard = NULL;//board to store while hint is calculated

}
//allocate the gameboard and the tempboard
void Board::newboard()
{
  board = new int *[dimen];
  
  for (int i = 0; i < dimen; i++)
    board[i] = new int[dimen];

  for(int i = 0; i < dimen; i++)
    for (int j = 0; j < dimen; j++)
      board[i][j] = 0;

  newtile();
  newtile();
  first_tiles = false;//first_tiles set to false after they are placed

//allocate tempboard for later use
  tempboard = new int *[dimen];
  
  for (int i = 0; i < dimen; i++)
    tempboard[i] = new int[dimen];

  for(int i = 0; i < dimen; i++)
    for (int j = 0; j < dimen; j++)
      tempboard[i][j] = 0;

}

//sets dimension for board if it is within range
void Board::set_dimen(int num)
{
  if (num > 2 && num < 7)
      dimen = num;
}

//returns dimension user chose
int Board::get_dimen()
{
  return dimen;
}

//setter for first_tiles bool
void Board::set_first_tiles(bool gamestart)
{
  first_tiles = gamestart;
}
//getter for first_tiles bool
bool Board::get_first_tiles()
{
  return first_tiles;
}

//prints out board with correct spacing
void Board::printboard(int score)
{
  cout << "CURRENT SCORE: " << score << endl;
  for (int i = 0; i < dimen; i++)
    {
      for (int j = 0; j < dimen; j++)
      {
        if (board[i][j] == 0)
          cout << "X" << "    ";
        else if (board[i][j] < 10)
          cout << board[i][j] << "    ";
        else if (board[i][j] > 9 && board[i][j] < 100)
          cout << board[i][j] << "   ";
        else if (board[i][j] > 99 && board[i][j] < 1000)
          cout << board[i][j] << "  ";
        else
          cout << board[i][j] << " ";
      }
      cout << endl << endl;
    }
}

//moves the board up, returns number > 0 if board moved at all
//uses amount_shift() on each tile
int Board::shift_up()
{
  int moved = 0;
    for (int i = 0; i < dimen; i++)
      for (int j = 0; j < dimen; j++)
        if ((board[i][j] != 0) && (i != 0))
        {
          int shift = amount_shift(i, j);
          if (shift != 0)
          {
            board[i - shift][j] = board[i][j];
            board[i][j] = 0;
            moved += shift;
          }
        }
      return moved;  
}

//calculates how much a tile can move up and returns it to shift_up()
int Board::amount_shift(int row, int column)
{
  int count = 0;
    for (int i = row - 1; i >= 0; i--)
     {
     if (board[i][column] == 0)
       {
          count++;
       }
     else
       return count;
    }
  return count;
}

//combines adjacent tiles if they are the same and returns score
int Board::combine()
{
  int score = 0;
      for(int i = 0; i < dimen - 1; i++)
        for (int j = 0; j < dimen; j++)
        {
          if (board[i][j] == board[i+1][j])
          {
            board[i][j] += board[i+1][j];
            board[i+1][j] = 0;     
            score += board[i][j];
          }
        }

    return score;
}

//rotate board if user enters anything but "w" to face "up" so
//the shift_up and combine and shift_amount functions can be used
//on any direction, and then rotate the board back to correct orientation
void Board::rotate(int diff)
{
  //rotate enough times to make the board face "up" before move
  //diff is a parameter based on the direction user chooses
  while (diff > 0)
  {
    int n = dimen;
    // dimen/2 = the amount of layers that need to be rotated
    //in a 4x4 board both the outer and inner layer are rotated (2)
    //dividing n/2 works because if the dimension is odd, the center
    //layer of the board is not rotated anyway, and the integer division
    //gets rid of an added layer rotation (5/2 = 2 layers rotated)
    int temp_tile;
    //four tiles are shifted at a time, temp saves the value of
    //the first tile shifted

    for (int i = 0; i < (n/2); i++)
      for (int j = i; j< (n-i-1); j++)
      {
        temp_tile = board[i][j];
        board[i][j] = board[j][n-i-1];
        board[j][n-i-1] = board[n-i-1][n-j-1];
        board[n-i-1][n-j-1] = board[n-j-1][i];
        board[n-j-1][i] = temp_tile;
      }
    diff--;
  }
}

//uses rotate(), shift_up, and combine to move board
int Board::moveboard(char move)
{
  int diff = 0;
  if (move == 'w')
    diff = 0;
  else if (move == 'a')
    diff = 1;
  else if (move == 's')
    diff = 2;
  else if (move == 'd')
    diff = 3;

  rotate(4 - diff);//make board face up

  int score = 0;

  int moved = shift_up();//move up
  score = combine();//combine tiles
  moved += shift_up();//move up again

  rotate(diff);//rotate back to original orientation

  //only add new tile if the board moved at all
  if (moved > 0 || score > 0)
  {
    newtile();
  }

  return score;//return score of the move
}

//gives user the move that generates the highest score
//by simulating all the moves and determining which one 
//is the best. stores board in temp board while it does this
char Board::give_hint()
{
    for (int i = 0; i < dimen; i++)
      for (int j = 0; j < dimen; j++)
        tempboard[i][j] = board[i][j];

  char move, bestmove = 'x';
  int bestscore = 0;
  int count = 0;

  while (count < 4)
  { 
    if (count == 0)
      move = 'w';
    else if (count == 1)
      move = 'a';
    else if (count == 2)
      move = 's';
    else 
      move = 'd';

    //find move with highest score
    int score = moveboard(move);
    if (score > bestscore)
    {
      bestscore = score;
      bestmove = move;
    }

    for (int i = 0; i < dimen; i++)
      for (int j = 0; j < dimen; j++)
        board[i][j] = tempboard[i][j];

    count++;
  }

  //if function returns 'x', then all moves have score = 0
  return bestmove;

}

//place new tile on edge of the board - 90% chance of 2 and 10% for 4
void Board::newtile()
{
  srand(time(NULL));

  int newtile;

  bool done = false;

  while (!done)
  {
    int placer = rand()%10 + 1;
    if (placer == 10 && !first_tiles)
      newtile = 4;
    else
      newtile = 2;

    int rand1 = rand()%2;
    if (rand1 == 1)
      rand1 = (dimen - 1);

    int rand2 = rand()%dimen;
    int index = rand()%2;

    if (index == 0 && board[rand1][rand2] == 0)
    {
      board[rand1][rand2] = newtile;
      done = true;
    }
    else if (index == 1 && board[rand2][rand1] == 0)
    {
      board[rand2][rand1] = newtile;
      done = true;
    }
  }
}

//checks for zeros and if adjacent tiles are the same
//if they are, returns false, if not -- gameover
bool Board::checklose()
{
  bool gameover = true;

  for (int i = 0; i < dimen; i++)
    for (int j = 0; j < dimen; j++)
      if (board[i][j] == 0)
      {
        gameover = false;
        return gameover;
      }

  for (int i = 0; i < (dimen - 1); i++)
    for (int j = 0; j < dimen; j++)
        if (board[i][j] == board[i+1][j])
        {
          gameover = false;
          return gameover;
        }

  for (int i = 0; i < dimen; i++)
    for (int j = 0; j < (dimen - 1); j++)
        if (board[i][j] == board[i][j+1])
        {
          gameover = false;
          return gameover;
        }

  return gameover;
}

//destructor for tempboard and board
Board::~Board()
{
  delete [] *board;
  delete [] board;

  delete [] *tempboard;
  delete [] tempboard;

}