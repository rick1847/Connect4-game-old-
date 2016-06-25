/*
File functions header
@Project: ICS3UI
@Student: Richard Tu 
@Date: June 15 2016
**/

#ifndef ACCOUNTSANDSCORE_TXT
#define ACCOUNTSANDSCORE_TXT
#include <string>
#include <fstream>

//get move function (also used for files)
int get_move();
//class Account
class Account{
private:
	//stores account number, then the name, then wins, losses and ties as private
	int accNumb;
	char name[15];
	int wins;
	int losses;
	int ties;
public:
	//constructor
	Account(std::string = "", int = 0, int = 0, int = 0, int = 0);
	//set funcs
	void setName(std::string);
	void setWins(int);
	void setLoss(int);
	void setTies(int);
	void setAccNumb(int);
	//set funcs end

	//get funcs start
	std::string getName();
	int getWins();
	int getLoss();
	int getTies();
	int getAccNumb();
	//get funcs end
};
//wipes the file clean (also seeds a blank file)
void fileCreator(std::fstream & );
//creates an account
void AccCreator(std::fstream & );
//deletes an account
void AccDelete(std::fstream & );
//updates the name of an account
void AccUpdate(std::fstream & );
//prints out the stuff in a Account class
void outputLine(Account &);
//prints out the stuff in a file
void printout(std::fstream &);
//Prints out the leader board
void printout_leaderboard(std::fstream &);

#endif
