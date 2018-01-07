/***************** 
* Sammy Stolzenbach
* COMP11
* HW7
* 2048 Game header file
******************/

#include <iostream>
#include "Board.h"
#include "Scores.h"
using namespace std;

#ifndef GAME_H_
#define GAME_H_

class Game
{
 private:
  bool lose; //bool for if the game is over
  char move; //players direction/move choice for the board
  int score; //players current score
  Board gameboard; //board object
  Scores leaderboard; //object for file I/O actions
  
 public:
  Game();//constructor

  //setters and getters
  void set_move(char);
  char get_move();

  void set_score(int);
  int get_score();

  void set_lose(bool);
  bool get_lose();

  void newgame(int dimen);
  //uses: gameboard.set_dimen(dimen)
  //      gameboard.newboard() 
  //      gameboard.printboard(score)

  bool checklose();
  //uses: bool taketurn
  //      returns true when player loses


  //function gets key from user, moves the board, updates score, adds new 
  //tile and returns if the loser has lost or not. also displays scores 
  //if user enters h, and shows hint if user enters ?
  bool taketurn(char);
  //uses: set_move(move)
  //      score += gameboard.moveboard(move)
  //      gameboard.newtile();
  //      gameboard.printboard();
  //      return gameboard.checklose;
  //      uses show_highscores and give_hint if necessary

  void bank_highscore(string);
  //at the end of a game, bank the player's name and score in the leaderboard file
  //and display the top 5 scores
};
  
#endif
