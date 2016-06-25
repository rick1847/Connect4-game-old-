/*
A.I header file
@Project: ICS3UI
@Student: Richard Tu 
@Date: June 15 2016
**/

//includes the header of board.h
#include "Connect4_board.h"
//change the hereustic checker to a add 3 check the one that isn't the same instead of checking for 4, starting from a certain move;


class Connect4_Computer{
private:
	int difficulty;

public:

	Connect4_Computer(int );
	//hereustic functions
	int triple_checker2(int** b);
	int triple_checker(Connect4_board, char );
	int hereustic(Connect4_board , int );

	//getting and setting the difficulty
	int get_difficulty();
	void set_difficulty(int );

	//returns minimum and maximum
	int min(int , int );
	int max(int , int );
	
	//the recursive function
	int advantage(Connect4_board , int , int , int );

	//chooses the move and runs advantage
	int move_chooser(Connect4_board , int );
	
	//shifts the elements of an array from a certain point up and the element from the certain point to the end
	void array_pusher(int [], int );
};
