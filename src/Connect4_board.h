/*
Board header file
@Project: ICS3UI
@Student: Richard Tu 
@Date: June 15 2016
**/

class Connect4_board{

private:
	char board[8][8];//this is the board which we play on

	//letters used, - for neutral, o for first player, x for second player
	//the second [] is for row
public:
	
	Connect4_board();//constructor
	~Connect4_board();//destructor (prevents segmentation fault)
	void test_print();//prints out the board
	bool do_a_move(int, char);//Does a move
	bool undo_a_move(int);//undoes a move
	bool checker_win();//checks for a win
	bool checker_tie();//checks for a tie
	bool checker_allowed(int);//checks for validity of move (for computer so that it doesn't break)
	char return_arr_val(int , int);//returns the value in the board array
};
