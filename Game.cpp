/***************** 
* Sammy Stolzenbach
* COMP11
* HW7
* 2048 Game.cpp 
******************/

#include <iostream>
#include <iostream>
#include "Game.h"
using namespace std;

//Game constructor
Game::Game()
{
  score = 0;
  lose = false;
  move = ' ';
}

//setter for score
 void Game::set_score(int num)
 {
  if (num >= 0)
    score = num;
 }
//getter for score
int Game::get_score()
{
  return score;
}

//setter or move
void Game::set_move(char shift)
{
  if (shift == 'a' || shift == 's' || shift == 'd' || shift == 'w'
      || shift == 'h' || shift == 'q' || shift == '?')
    {
      move = shift;
    }
  else
  {
    cout << "Invalid key. Try again.\n";
  }
}
//getter for score
char Game::get_move()
{
  return move;
}
//setter for bool lose
void Game::set_lose(bool gameover)
{
  lose = gameover;
}
//getter for bool lose
bool Game::get_lose()
{
  return lose;
}

void Game::newgame(int num)
{
  //count existing scores if they exist
  //and desplay highscore
  leaderboard.count_scores();
  //allocate score and name arrays
  leaderboard.allocate();

  //create new board and print it
  gameboard.set_dimen(num);
  gameboard.newboard();
  gameboard.printboard(score);
}

bool Game::taketurn(char shift)
{
  
  set_move(shift); 
  if (move != 'q' && move != 'h')
  {
    char key = move;
    if (move == '?')
    {
      char bestmove = gameboard.give_hint();
      if (bestmove != 'x')
        cout << "Hint: a good move is " << bestmove << endl;
      else
        cout << "Hint: any move is fine.\n";//all moves have score 0

      return lose;
    }
    score += gameboard.moveboard(key);
    int num = score;
    gameboard.printboard(num);
    lose = gameboard.checklose();//if they move the board check for loss
    return lose;
  }
  else if (move == 'q')//end game if they quit
  {
    lose = true;
    return lose;
  }
  else if (move == 'h')//display high scores
  {
    leaderboard.show_scores();
    return lose;
  }
  return lose;
}

void Game::bank_highscore(string player)
{
  leaderboard.set_player(player);
  int num = score;
  leaderboard.bank_score(num);
  leaderboard.show_scores();
  leaderboard.update_scores();
}




