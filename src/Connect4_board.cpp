/*
Connect 4 board functions
@Project: ICS3UI
@Student: Richard Tu 
@Date: June 15 2016
**/

//includes
#include "Connect4_board.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <iomanip>

using std::cout;
using std::cin;
using std::string;
using std::endl;

	//constructor which initializes all elements of the board to '-'
	Connect4_board::Connect4_board(){
		for (int count = 0; count < 8; count++){
			for(int count2 = 0; count2 < 8; count2++){
				board[count][count2] = '-';
			}
		}
	}

	//destroys the board once the function exits (apparently arrays aren't cleared by exiting a function)
	Connect4_board::~Connect4_board(){
		;
	}

	//prints out the board
	void Connect4_board::test_print(){
		for (int count = 0; count < 8; count++){
			for(int count2 = 0; count2 < 8; count2++){
				cout<<board[count][count2]<<"   ";//double space for clarity
			}
			cout<<endl<<endl;//double newline for clarity
		}
		cout<<"1   2   3   4   5   6   7   8"<<endl;//outputs the columns
	}

	//does a move on the board, returns false if it isn't possible
	bool Connect4_board::do_a_move(int move, char a){
		move = move - 1;//subtracts move by 1 (most people done't start counting from 0)
		if (move > 7){//if it is greater than 7 return false
			return false;
		}
		else if (move < 0){//if it is less than 0 
			return false;//return false
		}
		else if(checker_allowed(move) == false){
			return false;
		}
		int count = 7;//starts count at 7 (the bottom of the board)

		while (count >= 0){//checks all elements in the row
			if (board[count][move] == '-'){//if the element is equal to the original value in the constructor
				board[count][move] = a;//set it equal to a
				return true;//return out
			}
			else {
				count--;//decrement to check the next element (it goes up) (un-intuitive but works)
			}
		}

		return false;//if it is not possible then return false
	}

	//undos a move (for the computer)
	bool Connect4_board::undo_a_move(int move){
		move--;//subtracts by one to keep in format with do_a_move

		int count = 0;//starts from the top
		while (count < 8){//goes down until the array reaches element 7
			if (board[count][move] != '-'){//checks to see if the board element is not the original char ('-')
				board[count][move] = '-';//sets the element to the original char
				return true;//returns out
			}
			else {
				count++;//count increments
			}
		}
		//legacy stuff
		if (board[count][move] != '-'){
			board[count][move] = '-';
		}//legacy stuff end
		return false;//return out
	}

	//checks for a win
	bool Connect4_board::checker_win(){
		//for all the below functions, it checks if all four elements in a row equal eachother, 
		//then checks if one of those elements does not equal '-'
		//if it isn't then it returns true
		//otherwise it returns false

		//for horizontal
		for(int count = 0; count < 8; count++){
			for(int count2 = 0; count2 < 5; count2++){
				if(board[count][count2] == board[count][count2 + 1] 
					&& board[count][count2 + 1] == board[count][count2 + 2]
					&& board[count][count2 + 2] == board[count][count2 + 3]
					&& board[count][count2] != '-'){

					return true;
				}
			}
		}

		//for vertical
		for(int count = 0; count < 8; count++){
			for(int count2 = 0; count2 < 5; count2++){
				if(board[count2][count] == board[count2 + 1][count]
					&& board[count2 + 1][count] == board[count2 + 2][count]
					&& board[count2 + 2][count] == board[count2 + 3][count]
					&& board[count2][count] != '-'){

					return true;
				}
			}
		}

		//for diagonal 1
		for(int count = 0; count < 5; count++){
			for(int count2 = 0; count2 < 5; count2++){
				if(board[count][count2] == board[count + 1][count2 + 1]
					&& board[count + 1][count2 + 1] == board[count + 2][count2 + 2]
					&& board[count + 2][count2 + 2] == board[count + 3][count2 + 3]
					&& board[count][count2] != '-'){

					return true;

				}
			}
		}

		//for diagonal 2
		for(int count = 0; count < 5; count++){
			for(int count2 = 0; count2 < 5; count2++){
				if(board[count][count2 + 3] == board[count + 1][count2 + 2]
					&& board[count + 1][count2 + 2] == board[count + 2][count2 + 1]
					&& board[count + 2][count2 + 1] == board[count + 3][count2]
					&& board[count][count2 + 3] != '-'){

					
					return true;

				}
			}
		}
		
		return false;
	}

	//checks for a tie
	bool Connect4_board::checker_tie(){
		bool check = true;//assumes there is a tie
		//checks the top of each column
		for(int count2 = 0; count2 < 8; count2++){
			if (board[0][count2] == '-'){//if it is equal to the original char ('-')
				check = false;//check equals false
				count2 = 10;//set count 2 anything higher than the end condition to exit
			}
		}
		
		return check;//return check
	}
	
	//for the a.i only
	//checks to see if the move is possible
	bool Connect4_board::checker_allowed(int move){
		
		if (board[0][move] == '-'){//checks if the top of the column is empty
			return true;//if it is return true
		
		}
		else {
			return false;//else return false
		}
	}

	//returns the value of the element
	char Connect4_board::return_arr_val(int x, int y){
		return board[x][y];
	}
