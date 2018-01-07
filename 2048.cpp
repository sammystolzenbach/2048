/***************** 
* Sammy Stolzenbach
* COMP11
* HW7
* 2048 Driver 
******************/
#include <iostream>
#include "Game.h"
using namespace std;

int main()
{
  
  Game mygame;//create game object
  cout << "Welcome to 2048!\n";

  char difficulty;//extra credit -- difficulty based on board dimension
  int dimen;
  cout << "What difficulty would you like?\n Enter e for easy, m for medium"
       << " and h for hard.\n";

  do //enforce correct input for difficulty
  {
    cin >> difficulty;
    
    if (difficulty != 'e' && difficulty != 'm' && difficulty != 'h')
      cout << "Enter e, m, or h please:\n";

  } while (difficulty != 'e' && difficulty != 'm' && difficulty != 'h');

  if (difficulty == 'e')
    dimen = 5;
  else if (difficulty == 'm')
    dimen = 4;
  else
    dimen = 3;

  mygame.newgame(dimen);//create new board

  char move;
  bool gameover = false;

  cout << "w-a-s-d is the keyboard. Enter h to see highscores, "
       << " q to quit, and ? for a hint\n";

  while (!gameover)//until take_turn returns true for gameover
  {
    do//enforce correct input
    { 
      cout << "Enter a move (w-a-s-d q,h,?):\n";
      cin >> move;

      if (move != 'a' && move != 'w' && move != 'd' && move !='s'
         && move != 'q' && move != 'h' && move != '?')
      {
         cout << "Invalid key. Try again.\n";
      }

    } while (move != 'a' && move != 'w' && move != 'd' && move != 's'
            && move != 'q' && move != 'h' && move != '?');

    gameover = mygame.taketurn(move);
  }

  //get users score
  int score = mygame.get_score();
  cout << "Game over. Your score is " << score << endl;

  string name;
  cout << "What is your player name?\n";//get name of player for high scores
  cin >> name;

  //update and display high scores
  mygame.bank_highscore(name);

  return 0;
}
