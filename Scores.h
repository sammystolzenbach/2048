/***************** 
* Sammy Stolzenbach
* COMP11
* HW7
* 2048 Scores header file
******************/

#include <iostream>
using namespace std;

#ifndef SCORES_H_
#define SCORES_H_

const char SCOREFILE[] = "highscores.txt";

class Scores
{
private:
	string player; //attribute for current players name
	int high_score; //attribute for players score at the end of the game
	bool no_scores; //bool for if high-scores exist or not
	int filecount; //attribute for size of the dynamic arrays
	string *names; //pointer for dynamic arrays for names
	int *scores; //pointer for dynamic arrays for scores

public:
	//default constructor
	Scores();

	//setters and getters
	void set_player(string);
	string get_player();

	void set_high_score(int);
	int get_high_score();

	void count_scores();
	//counts the number of scores in the highscore file to get 
	//size for dynamic arrays

	void allocate();
	//reads in from the highscore file and allocates the name
	// and score arrays, leaving room for one more name and score
	// for the person currently playing the game

	void show_scores();
	//print the first five scores/names if the player enters h

	void bank_score(int);
	//at the end of a game, put the players name and score into the right 
	//spot of the arrays of names ans scores

	void update_scores();
	//writes the updated array (with the players name and score) and
	//writes it to the file

	//destructor for dynamic arrays
	~Scores();
};

#endif