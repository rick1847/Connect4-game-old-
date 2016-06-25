/*
Connect 4 other main functions
@Project: ICS3UI
@Student: Richard Tu 
@Date: June 15 2016
**/

//includes
#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>

#include "Connect4_player.h"
#include "Connect4_computer.h"

using std::cout;
using std::cin;
using std::string;
using std::endl;

//This function takes in the integer for winner, the two Accounts and the file to print out the winner and save it to a file
void who_won(int winner, Account & play1, Account & play2, std::fstream & file){
	cout<<endl;
	switch(winner){//switch statement
		case 1://if the winner is player 1, it adds a win to player 1 and adds a loss to player 2, and prints that player 1 wins
		cout<<play1.getName()<<" wins";
		play1.setWins(play1.getWins() + 1);
		play2.setLoss(play2.getLoss() + 1);
		break;
		case 2://if the winner is player 2, it adds a win to player 2 and adds a loss to player 1, and prints that player 2 wins
		cout<<play2.getName()<<" wins";
		play2.setWins(play2.getWins() + 1);
		play1.setLoss(play1.getLoss() + 1);
		break;
		default://if there is no winner (Winner = 0) then it adds one tie to both, and prints that its a tie
		cout<<"its a tie";
		play1.setTies(play1.getTies() + 1);
		play2.setTies(play2.getTies() + 1);
		break;

	}
	cout<<endl<<endl;
	if(play1.getAccNumb() > 0){//checks if the account number is greater than 0, if it is, then it will save it to the file
		file.seekp((play1.getAccNumb() - 1) * sizeof(Account));
		file.write(reinterpret_cast<char *>(&play1), sizeof(Account));
	}
	if(play2.getAccNumb() > 0){//checks if the account number is greater than 0, if it is, then it will save it to the file
		file.seekp((play2.getAccNumb() - 1) * sizeof(Account));
		file.write(reinterpret_cast<char *>(&play2), sizeof(Account));
	}
	return ;
}

//this function runs single player
void single_player(std::fstream & m){
	//creates two blanks so that I can run the who won function
	Account blank1("Player",-2);
	Account blank2("Computer",-2);
	int diff = 0;
	//get a valid difficulty amount
	while(diff != 2 && diff != 4 && diff != 5 ){//checks to see if the difficulty is a valid difficulty
		cout<<"Do you want easy(1), normal(2), or hard(3)difficulty ";
		diff = get_move();//uses get_move() function to get the difficulty
		switch (diff){
			case 1://easy difficulty recurses 2 layers
			diff = 2;
			break;
			case 2://normal difficulty recurses 4 layers
			diff = 4;
			break;
			case 3://Hard difficulty recurses 5 layers
			diff = 5;
			break;
			default://tells user that the number they entered in is invalid
			diff = 0;
			cout<<"invalid number"<<endl;
			break;
		}
	}

	Connect4_board board;//creates a board
	Connect4_Computer comp(diff);
	bool win = false;//for saying whether or not the game is still going
	int winner = 0;//for saying who won (1 for p1, 2 for p2, 0 for tie)
	bool allowed = false;//This determines validity of the move
	int move;//determines move number

		while (win == false){//a while loop to run the game

			allowed = false;//always sets allowed to false
			board.test_print();//prints the board

			cout<<"Player go, which column do you choose ";
			move = get_move();//gets user input
			allowed = board.do_a_move(move, 'o');//enters the move in the board
			while (allowed == false){//if the move isn't possible then it will tell you that the move is invalid and continue to get moves until it is valid
				cout<<"invalid move, please go again ";
				move = get_move();
				allowed = board.do_a_move(move, 'o');
			}

			win = board.checker_win();//checks if there is a winner
			if (win == true){//if there is assign 1 to winner and continue
				winner = 1;
				continue;

			}
			win = board.checker_tie();//checks if there is a tie
			if (win == true){//if there is continue
				continue;
			}

			board.test_print();//shows you made a move
			move = comp.move_chooser(board, comp.get_difficulty());//gets the computer player's move
			cout<<"Computer move is "<<move<<endl;//prints out the computer's move
			board.do_a_move(move, 'x');//enters the move into the board

			win = board.checker_win();//if the computer wins it assigns 2 to winner and continues
			if (win == true){
				winner = 2;
				continue;

			}
			win = board.checker_tie();//checks if there is a tie
			if (win == true){//if there is continue
				continue;
			}
	}
	board.test_print();//prints out the last board which shows how the winning board
	who_won(winner, blank1, blank2, m);//prints out who won
	//finish up the part where it displays who won
}

//this function runs two player, and takes the accounts and a file object as parameters (to print out the correct names and for who_won function)
void multi_player(Account & player1,Account & player2, std::fstream & file){
	Connect4_board board;//creates the board
	bool win = false;//determines if there is a win or tie
	bool allowed = false;//determines validity of the move
	int move;//stores the move
	int player = 0;//stores the value of the winning player (1 for p1, 2 for p2, 0 for tie)
	while (win == false){//while loop runs the game
		allowed = false;//turns allowed to false before getting p1's move
		board.test_print();//prints the board
		cout<<player1.getName()<<" go, what move do you choose ";
		move = get_move();//gets p1's move
		allowed = board.do_a_move(move, 'o');//inputs move, returns false if it can't
		while (allowed == false){//if the move is invalid it continues until it can get a move
			cout<<"invalid move, please go again ";
			move = get_move();
			allowed = board.do_a_move(move, 'o');
		}

		win = board.checker_win();//checks for a winner
		if (win == true){//if there is assign 1 to player and continue
			player = 1;
			continue;
		}
		win = board.checker_tie();//checks if there is a tie
		if(win == true){//if there is continue (player is set to 0)
			continue;
		}

		board.test_print();//prints out the board
		allowed = false;//sets allowed to false for p2's move
		cout<<player2.getName()<<" go, which column do you choose ";
		move = get_move();//gets p2's move
		allowed = board.do_a_move(move, 'x');//inputs move, if it can't then it returns false
		while (allowed == false){//if the move is invalid it continues to ask until it gets a valid move
			cout<<"invalid move, please go again ";
			move = get_move();
			allowed = board.do_a_move(move, 'x');
		}
		win = board.checker_win();//checks for a win
		if(win == true){//if there is assign 2 to player and continue
			player = 2;
			continue;
		}

		win = board.checker_tie();//checks for a tie
		if(win == true){//if there is it continues
			continue;
		}
	}

	board.test_print();//prints out the last move
	who_won(player, player1, player2, file);//displays who won
}

//this functions sets up the account for two player
void identification(std::fstream & saveGame){
	int a = 0;//stores the original account number
	bool id_done = false;//Says whether the id is done
	Account player1;//this is Account for p1
	Account player2;//this is Account for p2



	while (id_done == false){//id for player 1
		printout(saveGame);//prints out the current active accounts
		cout<<"What is your account number player 1 (1-100) (0 for no account)\nIf you are not in the list enter 101";
		a = get_move();//gets their account number
		if(a == 0){//if a = 0, it sets a default account called player 1
			player1.setAccNumb(-1);
			player1.setName("Player 1");
			id_done = true;

		}
		else if(a == 101){
			AccCreator(saveGame);		
		}
		
		else if (a > 0 && a < 101){//gets the account and assigns it to player1
			
			saveGame.seekg((a - 1) * sizeof(Account));
			saveGame.read(reinterpret_cast<char *>(&player1), sizeof(Account));
			if(player1.getAccNumb() != 0){//if it doesn't equal 0 it is actually assigns it
				id_done = true;
			}
			else{
				cout<<"Invalid number "<<endl;
			}
			
		}
		else{//else it is an invalid number
			cout<<"Invalid number "<<endl;
		}
	}
	id_done = false;//sets id_done to false for player2


	while (id_done == false){
		printout(saveGame);//prints out the available accounts
		cout<<"What is your account number player 2 (1-100) (0 for no account)\nIf you are not in the list enter 101";//gets the second player's account number
		a = get_move();
		if(a == 0){//if a is equal to 0 set the account as a generic account with name player 2
			player2.setAccNumb(-1);
			player2.setName(string("Player 2"));
			id_done = true;
		}
		else if(a == player1.getAccNumb()){
			cout<<"Don't play yourself "<<endl;
		}
		else if(a == 101){
				AccCreator(saveGame);
		}
		else if (a > 0 && a < 101){//else it gets the account from the file
			player2.setAccNumb(a);
			saveGame.seekg((a - 1) * sizeof(Account));
			saveGame.read(reinterpret_cast<char *>(&player2), sizeof(Account));

			if(player2.getAccNumb() != 0){//if it does not equal 0 then it is assigned
				id_done = true;
			}
			else{
				cout<<"Invalid number "<<endl;
			}
		}
		else{
			cout<<"Invalid number "<<endl;
		}
	}
	multi_player(player1, player2, saveGame);//runs multiplayer
}

//runs the file functions
void file_stuff(std::fstream & file){
	int selection = 1;//gives you a selection
	while(selection != 0){//everything in a selection loop
		cout<<"Would you like to:\n"//shows you your options
			<<"See the leaderboards(1)\n"
			<<"Create an Account(2)\n"
			<<"Change the name of an Account(3)\n"
			<<"Delete an Account(4)\n"
			<<"Wipe the File(5)\n"
			<<"Exit(6)";
		selection = get_move();//gets move
		switch(selection){
			case 1:
				printout_leaderboard(file);//prints the contents of the file
				break;
			case 2:
				AccCreator(file);//creates an account
				break;
			case 3:
				AccUpdate(file);//changes the name of the account
				break;
			case 4:
				AccDelete(file);//deletes an account
				break;
			case 5:
				fileCreator(file);//wipes the file blank
				break;
			case 6:
				return;//exits the function
			default:
				cout<<"Invalid input"<<endl;

		}
	}
}
