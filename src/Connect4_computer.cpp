/*
Connect 4 computer a.i
@Project: ICS3UI
@Student: Richard Tu 
@Date: June 15 2016
**/

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include "Connect4_computer.h"

using std::cout;
using std::cin;
using std::string;
using std::endl;

struct thing{
	char board[8][8];
};

	//the constructor
	Connect4_Computer::Connect4_Computer(int diff){
		set_difficulty(diff);//technically does store a difficulty
	}

	//second triple checker checks for stacked triples
	int Connect4_Computer::triple_checker2(int** b){
		int amount = 0;
		//uses the array b to determine whether or not there are stacks any and adds 20 to the amount
		for(int i = 0; i < 7; i++){
			for(int v = 0; v < 7; v++){
				if(b[i][v] == 1){
					if(b[i + 1][v] == 1){
						amount += 25;
					}
					if(b[i][v + 1] == 1){
						amount += 25;
					}
					if(b[i + 1][v + 1] == 1){
						amount += 25;
					}
				}
			}
		}
		
		//cout<<amount;
		return amount;
	}

	//checks for triples
	int Connect4_Computer::triple_checker(Connect4_board board, char a){
		thing eval_board;//creates a struct with a board in it

		//copies everything from board over for evaluation
		for(int count = 0; count < 8; count++){
			for(int count2 = 0; count2 < 8; count2++){
				eval_board.board[count][count2] = board.return_arr_val(count,count2);
			}
		}

		//creates a second array for ints
		int ** comp_grid = new int *[8];
		for(int i = 0; i < 8; i++){
			comp_grid[i] = new int[8];
		}
		//initializes all elements to 0
		for(int i = 0; i < 8; i++){
			for(int v = 0; v < 8; v++){
				comp_grid[i][v] = 0;
			}
		}

		int triple_amount = 0;//stores the amount of triples formed
		int triple = 0;//stores the amount of pieces in a row
		int xcoor;//stores the x coordinate of the empty space
		int ycoor;//stores the y coordinate of the empty space

		//checks for all possible horizontal triples
		for(int count = 0; count < 8; count++){//this for height offset
			for(int count2 = 0; count2 < 5; count2++){//this for length offset (I do sort of switch x and y)
				triple = 0;//sets triple to 0 at the start of every check

				//evaluates whether the next 4 elements in the array is equal to >a<, if they are then add 1 to the triple , if not
				//set the xcoor and y coord to count and count2
				//the rest of the evaluation sets follow this format
				//then evaluates whether or not the move has a double set if triple is equal to 2
				if(eval_board.board[count][count2] == a){
					triple++;
				}
				else{
					xcoor = count;
					ycoor = count2;
				}
				if(eval_board.board[count][count2 + 1] == a){
					triple++;
				}
				else{
					xcoor = count;
					ycoor = count2 + 1;
				}
				if(eval_board.board[count][count2 + 2] == a){
					triple++;
				}
				else{
					xcoor = count;
					ycoor = count2 + 2;
				}
				if(eval_board.board[count][count2 + 3] == a){
					triple++;
				}
				else{
					xcoor = count;
					ycoor = count2 + 3;
				}

				if(triple == 3 && eval_board.board[xcoor][ycoor] == '-'){//if there are 3 pieces that make up the triple (will skip 4s)
					//and the board has an empty spot ("-" means empty) it will add 1 to triple_amount and set the comp_grid(position) to 1
					triple_amount += 5;
					comp_grid[xcoor][ycoor] = 1;
				}
				else if (triple == 2){
					for(int i = count2; i < count2 + 3; i++){
						if(eval_board.board[count][i] == '-'){
							triple++;
						}
					}
					if (triple <= 4){
						triple_amount += 1;
					}
				}
				else{
					;
				}
			}
		}

		for(int count = 0; count < 8; count++){
			for(int count2 = 0; count2 < 5; count2++){
				triple = 0;
				if(eval_board.board[count][count2] == a){
					triple++;
				}
				else{
					xcoor = count;
					ycoor = count2;
				}
				if(eval_board.board[count + 1][count2] == a){
					triple++;
				}
				else{
					xcoor = count + 1;
					ycoor = count2;
				}
				if(eval_board.board[count + 2][count2] == a){
					triple++;
				}
				else{
					xcoor = count + 2;
					ycoor = count2;
				}
				if(eval_board.board[count + 3][count2] == a){
					triple++;
				}
				else{
					xcoor = count + 3;
					ycoor = count2;
				}

				if(triple == 3 && eval_board.board[xcoor][ycoor] == '-'){
					triple_amount += 5;
					comp_grid[xcoor][ycoor] = 1;
					
				}
				else if (triple == 2){
					for(int i = count; i < count + 3; i++){
						if(eval_board.board[i][count2] == '-'){
							triple++;
						}
					}
					if (triple <= 4){
						triple_amount += 1;
					}
				}
				else{
					;
				}
			}
		}

		for(int count = 0; count < 5; count++){
			for(int count2 = 0; count2 < 5; count2++){
				triple = 0;
				if(eval_board.board[count][count2] == a){
					triple++;
				}
				else{
					xcoor = count;
					ycoor = count2;
				}
				if(eval_board.board[count + 1][count2 + 1] == a){
					triple++;
				}
				else{
					xcoor = count + 1;
					ycoor = count2 + 1;
				}
				if(eval_board.board[count + 2][count2 + 2] == a){
					triple++;
				}
				else{
					xcoor = count + 2;
					ycoor = count2 + 2;
				}
				if(eval_board.board[count + 3][count2 + 3] == a){
					triple++;
				}
				else{
					xcoor = count + 3;
					ycoor = count2 + 3;
				}

				if(triple == 3 && eval_board.board[xcoor][ycoor] == '-'){
					triple_amount += 5;
					comp_grid[xcoor][ycoor] = 1;
					
				}
				else if (triple == 2){
					for(int i = count2; i < count2 + 3; i++){
						if(eval_board.board[i][i] == '-'){
							triple++;
						}
					}
					if (triple <= 4){
						triple_amount += 1;
					}
				}
				else{
					;//cout<<"diagonal "<<count<<" "<<count2<<" triple "<<triple<<endl;
				}
			}
		}
		for(int count = 0; count < 5; count++){
			for(int count2 = 0; count2 < 5; count2++){
				triple = 0;
				if(eval_board.board[count][count2 + 3] == a){
					triple++;
				}
				else{
					xcoor = count;
					ycoor = count2 + 3;
				}
				if(eval_board.board[count + 1][count2 + 2] == a){
					triple++;
				}
				else{
					xcoor = count + 1;
					ycoor = count2 + 2;
				}
				if(eval_board.board[count + 2][count2 + 1] == a){
					triple++;
				}
				else{
					xcoor = count + 2;
					ycoor = count2 + 1;
				}
				if(eval_board.board[count + 3][count2] == a){
					triple++;
				}
				else{
					xcoor = count + 3;
					ycoor = count2;
				}

				if(triple == 3 && eval_board.board[xcoor][ycoor] == '-'){
					triple_amount += 5;
					comp_grid[xcoor][ycoor] = 1;
					
				}
				else if (triple == 2){
					int v = count2; 
					for(int i = count; i < count + 3; i++){
						v = v - 1;
						if(eval_board.board[i][v] == '-'){
							triple++;
						}
					}
					if (triple <= 4){
						triple_amount += 1;
					}
				}
				else{
					;
				}
			}
		}
	
		triple_amount += triple_checker2(comp_grid);//adds the stacked triples onto triple amount


		return triple_amount;
		
	}

	//returns the difficulty
	int Connect4_Computer::get_difficulty(){
		return difficulty;
	}

	//sets the difficulty
	void Connect4_Computer::set_difficulty(int diff){
		difficulty = diff;
	}

	//returns the minimum
	int Connect4_Computer::min(int a, int b){
		if (a < b){
			return a;
		}
		else{
			return b;
		}
	}

	//returns the maximum
	int Connect4_Computer::max(int a, int b){
		if(a > b){
			return a;
		}
		else{
			return b;
		}
	}

	//checks the state of the board and determines whether or not it is more advantageous for player 1 or player 2
	int Connect4_Computer::hereustic(Connect4_board board, int player){
		
		int triple_o = triple_checker(board, 'o');//stores value from triple checker for o
		int triple_x = triple_checker(board, 'x');//stores value from triple checker for x
		int her_adv = triple_x - triple_o;//uses a subtraction to determine who has a better game state (maximizer - minimizer)
		
		return her_adv;//return the hereustic value
	/*	if(player == 1){//if it is the maximizing player ('x' player) return the value *-1 as I am subtracting the x amount)
			return her_adv;
		}
		else{//if not just return an unmodified hereustic value (player 0 is the minimizing player)
			return her_adv;
		}*/
	}
	
	//the recursive function which determines the advantage
	int Connect4_Computer::advantage(Connect4_board board, int move, int layer, int player){
		if (board.checker_allowed(move - 1) == false){//checks to see if it is possible to make a move
			return hereustic(board, player);
		}
		bool allowed = false;//unneeded garbage
		
		if(player == 0){//does the move as o if player is equal to 0
			allowed = board.do_a_move(move, 'o');//does the move
			if(board.checker_win() == true){//if it is a win return layer * -100 to show when it wins
				return (layer + 1) * -1000;
			}

		}
		//same as above but with x and without multiply by a negative number
		else if(player == 1){
			allowed = board.do_a_move(move, 'x');
			if(board.checker_win() == true){
				
				return (layer + 1) * 1000;
			}
		}

		if (layer == 0){//if the layer is 0 then return the hereustic function
			return hereustic(board, player);
		}
		
		
		
		int poss_moves[8];//for generating the possible moves
		int amount = 0;//counts the amount of possible moves
		bool possible = false;//shows whether or not it is possible
		for(int count = 0; count < 8; count++){//checks each column for a possible move
			possible = board.checker_allowed(count);//sets possible to either true or false
			if(possible == true){//if it is true
				poss_moves[amount] = count + 1;//set poss_moves[amount] to count + 1 in order to keep in line with do_a_move
				amount++;//increments count up
			}
		}

		int best_val;//stores the best vale depending on the player
		int v;//stores current value

		if (player == 1){
			best_val = 1000;//best value always set to worst value for player 1
			for(int count = 0; count < amount; count++){
				v = advantage(board, poss_moves[count], layer - 1, 0);//does a recursive call
				best_val = min(best_val, v);//stores the smallest of the two values as best_val
			}
		}

		//repeat player 1 except it is finding the max
		else if (player == 0){
			best_val = -1000;
			for(int count = 0; count < amount; count++){
				v = advantage(board, poss_moves[count], layer - 1, 1);
				best_val = max(best_val, v);
				/*if(best_val == (layer - 1)*100){
					count = 9;
				}*/
			}
		}
		return best_val;

	}

	int Connect4_Computer::move_chooser(Connect4_board board, int layer){

		//creates an array with the possible moves, all initialized to 0 because it is neutral
		int a[8] = {0,0,0,0,0,0,0,0};
		for(int i = 0; i < 8; i++){
			if(board.checker_allowed(i) == true){//checks to see if the move is possible
			//	cout<<"I'm called"<<endl;//shows that the function is being called (loading)
				a[i] = advantage(board, i + 1, layer - 1, 1);//calls the function and places the value inside the element i
			}
			else{//sets the element to a huge number so that it is placed at the end
				a[i] = -1000000;
			}
		}
		
		cout<<"Computer thinks:\n";
		for(int i = 0; i < 8; i++){
			cout<<"move "<<i + 1<<" has an advantage of "<<a[i]<<endl;
		}
		cout<<"\n";
		//array for the move order the computer will choose
		int moves[8];
		//copies over the moves from a[] and will later determine the move order
		int best_move[8];
		for(int i = 0; i < 8; i++){
			best_move[i] = a[i];
		}
		
		
		//organizes the best_move array from least to greatest
		bool changes = true;//says if a change has been made
		while(changes == true){
			changes = false;//assumes that no changes were made 
			for(int count = 0; count < 7; count++){//checks all elements of the array (up to seven due to organization)
				if(best_move[count] < best_move[count + 1]){//if the array element before it is smaller
					int place_holder = best_move[count + 1];//switch the two around
					best_move[count + 1] = best_move[count];
					best_move[count] = place_holder;
					changes = true;//set changes to true
				}
			}
		}


		bool done[] = {false,false,false,false,false,false,false,false};//this is to prevent entering the same move twice

		for(int count = 0; count < 8; count++){//checks all elements in the best_move array
			for(int i = 0; i < 8; i++){//checks all elements in a[]
				if(best_move[count] == a[i] && done[i] == false){//if the two match and the match hasn't been done before
					moves[count] = i + 1;//put in moves[count] i + 1 (to match with do_a_move function)
					done[i] = true;//sets the match to done already
					i = 8;//ends the comparison to move onto the next best_move
				}
			}
		}

		
		return moves[0];//returns the move to the sing_player function

	}

