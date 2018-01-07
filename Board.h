/***************** 
* Sammy Stolzenbach
* COMP11
* HW7
* 2048 Board header file
******************/

#include <iostream>

#ifndef BOARD_H_
#define BOARD_H_

class Board
{
 private:
  int dimen;//attribute for dimention of board
  int **board;//attribute for pointer to 2D array of ints
  bool first_tiles;//bool to make sure it wont set a 4 down if its a new game
  int **tempboard;//second dynamic 2D board to store board
  // while hint is calculated

 public:
  Board();
  //default constructer. Will point both boards to NULL

  //setters and getters for dimen and first_tiles
  void set_dimen(int dimen);
  int get_dimen();

  void set_first_tiles(bool gamestart);
  bool get_first_tiles();

  void newboard();
  //creates a new board (allocates the 2D array)
  //creates a tempboard 

  void printboard(int score);
  //prints the board and the current score
  //takes current score as a parameter
  
  void newtile();
  //sets a new tile down
  
  int amount_shift(int row, int column);
  //determines and returns amount that a tile can move up based on row and
  //column parameter. used in shift_up() on each tile in the array.

  void rotate(int diff); 
  //rotates the board 
  //used in moveboard() with functions shift_up() and combine();
  //integer parameter is the ammount of rotations to do based on what move 
  //user chooses.

  int combine(); 
  //combines tiles that have the same value and returns score 
  //that merge produces used in moveboard()

  int shift_up();
  //uses amount_shift() on each tile to determine how much tile can move, 
  //then moves based on that amount.
  //returns a number > 0 if the board has moved at all. If not, then
  //newtile() wont be added

  int moveboard(char move);
  //uses rotate(), shift_up(), and combine() to move the board based on 
  //move from the user, then returns the score that that move generates.

  char give_hint();
  //stores the board in a tempboard and simulates all moves and
  //returns the direction (wasd) that generates the best score

  bool checklose();
  //checks the board for a lose and returns true or false

  ~Board();//destructor for both 2D arrays

};

#endif

  

  


