/***************** 
* Sammy Stolzenbach
* COMP11
* HW7
* 2048 Scores.cpp
******************/

#include <iostream>
#include <fstream>
#include "Scores.h"

using namespace std;

Scores::Scores()
{
	high_score = 0;
	player = " ";
	names = NULL;
	scores = NULL;
	filecount = 0;
	no_scores = false;//set to true if no highscore file exists

}
//setter for playername
void Scores::set_player(string name)
{
	player = name;
}
//getter for player name
string Scores::get_player()
{
	return player;
}
//setter for player high score
void Scores::set_high_score(int score)
{
	high_score = score;
}
//getter for player high score
int Scores::get_high_score()
{
	return high_score;
}
//counts scores in current high score file 
//sets no_scores = true if no high scores exist
void Scores::count_scores()
{
	ifstream infile;

	infile.open(SCOREFILE);

	if (!infile.is_open())
	{
		cout << "There are no high-scores entered yet!" 
			 << " Your score will be the first.\n";
		no_scores = true;
		filecount = 0;
		return;
	}

	filecount = 0;
	string playername;
	int playerscore;
	while (!infile.eof())
	{
		infile >> playername >> playerscore;
		if (playername != "-1")
			filecount++;
	}

	infile.close();

}

//if high scores exist, allocates score and name arrays at the start
//of the game and cout the top high score
void Scores::allocate()
{

	names = new string[filecount+1];
	scores = new int[filecount+1];

	if (!no_scores)
	{
		ifstream infile;

		infile.open(SCOREFILE);

		if (!infile.is_open())
		{
			cout << "Error openning file.\n";
			return;
		}

		for (int i = 0; i < filecount; i++)
			infile >> names[i] >> scores[i];

		cout << "Top high-score is " << names[0] << ": "
			 << scores[0] << endl;
		cout << "Try to beat it!\n\n";
	}
}
	
//updates the highscore file - writes both arrays to highscores.txt
void Scores::update_scores()
{
	ofstream outfile;
	
	outfile.open(SCOREFILE);
	if (!outfile.is_open())
	{
		cout << "Error openning file.\n";
		return;
	}

	for (int i = 0; i < filecount; i++)
	{
		outfile << names[i] << " " << scores[i] << endl;
	}
	outfile << "-1";

	outfile.close();
}

//print the first five scores/names if the player enters h
void Scores::show_scores()
{
	if (filecount == 0)
	{
		cout << "No high-scores entered yet!\n";
		return;
	}
	int size;
	if (filecount < 5)
		size = filecount;
	else
		size = 5;

	cout << "Top " << size << " high-score(s):\n";
	for (int i = 0; i < size; i++)
		cout << names[i] << " " << scores[i] << endl;
	
}

//at the end of a game, put the players name and score into the right 
//spot of the arrays. Tells them if they have the new high score.
void Scores::bank_score(int score)
{
	int pos = filecount;
	for (int i = 0; i < filecount; i++)
		if (scores[i] <= score)
		{
			pos = i;
			break;
		}

	for (int i = filecount; i > pos; i--)
	{
		scores[i] = scores[i - 1];
		names[i] = names[i - 1];
	}

	scores[pos] = score;
	names[pos] = player;

	filecount++; 	

	if (pos == 0)
	{
		cout << "Congrats! You got the new high score!\n";
	}
}

//destructor for dynamic arrays
Scores::~Scores()
{
	delete []names;
	delete []scores;
}


