/*
Connect 4 file functions
@Project: ICS3UI
@Student: Richard Tu 
@Date: June 15 2016
**/

//includes
#include "Connect4_file.h"

#include <iostream>
#include <string>
#include <cstdlib>

#include <iomanip>
using std::cout;
using std::cin;
using std::string;
using std::endl;

//gets the move from the user
int get_move(){
	//two strings req for bullet proofing
	string selection, compare;
	//gets your selection
	cout<<"\n>";
	cin>>selection;
	cout<<endl;
	for(int count = 0; count < 110; count++){//compares your input to the to_string of count
		compare = std::to_string(count);
		if(selection == compare){//if they match return count
			return count;
		}
	}
	return -1;//if there is no match return -1
}
	//initializes all values to what is set in parameters (defaults in the header file)
	Account::Account(string name2, int accNumb2, int wins2, int losses2, int ties2){
		setName(name2);
		setWins(wins2);
		setLoss(losses2);
		setTies(ties2);
		setAccNumb(accNumb2);
	}
	//set funcs
	void Account::setName(string name2){
		int a = name2.size();//gets size
		a = (a < 14 ? a : 14);//makes sure size is less than 14 if not it will set it to 14
		name2.copy(name, a);//copies the string to the array
		name[a] = '\0';//puts EOF char to show that that is the end of the name
	}
	void Account::setWins(int wins2){
		wins = wins2;
	}
	void Account::setLoss(int loss2){
		losses = loss2;
	}
	void Account::setTies(int ties2){
		ties = ties2;
	}
	void Account::setAccNumb(int accNumb2){
		accNumb = accNumb2;
	}
	//set funcs end

	//get funcs start
	string Account::getName(){
		string n(name);
		return n;
	}
	int Account::getWins(){
		return wins;
	}
	int Account::getLoss(){
		return losses;
	}
	int Account::getTies(){
		return ties;
	}
	int Account::getAccNumb(){
		return accNumb;
	}
	//get funcs end

//creates a bunch of blank Account
void fileCreator(std::fstream & newfile){
	Account blank;
	int a = 0;
	while(a < 110){//writes 110 empty slots
		blank.setAccNumb(0);
		newfile.seekp(a * sizeof(Account));
		newfile.write(reinterpret_cast<char*>(&blank), sizeof(Account));
		a = a + 1;
	}
}

//all based off of AccCreator
//deletes your account from the file
void AccDelete(std::fstream & saveGame){
	int a = 0;
	bool created = false;//allows the loop to run
	Account newDude;//creates a blank Account
	printout(saveGame);//prints out the accounts in the file
	while(created == false){
		a = 0;//sets a = to zero always
		while(a <= 0 || a > 100){//runs while a is less than 1 or greater than 500
			cout<<"What is your account number to be (1-100)(0 to exit)";
			a = get_move();//gets your account number
			if (a == 0){//if a is equal to zero it returns out
				return;
			}
			if(a <= 0 || a > 100){//if it the same as the while condition it outputs that it is an invalid number
				cout<<"Invalid Account Number"<<endl;
			}//end first while loop
		}//end second while loop

		//writes blank to file
		saveGame.seekp((a - 1) * sizeof(Account));
		saveGame.write(reinterpret_cast<char *>(&newDude), sizeof(Account));
		created = true;//exits out of while loop
	}
	return;
}

//all based off of AccCreator
//updates the name of the account
void AccUpdate(std::fstream & saveGame){
	int a = 0;//stores account number
	string b;//stores new name
	bool created = false;//allows the loop to run
	Account newDude;//creates a blank Account
	printout(saveGame);//prints out the accounts in the file
	while(created == false){
		a = 0;//sets a to 0
		while(a <= 0 || a > 100){//runs while a is less than 1 or greater than 500
			cout<<"What is your account number (1-100)(0 to exit)";
			a = get_move();//gets account number
			if (a == 0){//if a is equal to zero it returns out
				return;
			}
			if(a < 0 || a > 100){//if it the same as the while condition it outputs that it is an invalid number
				cout<<"Invalid Account Number"<<endl;
			}//end first while loop
		}//end second while loop

		saveGame.seekg((a - 1) * sizeof(Account));//gets the account from the file
		saveGame.read(reinterpret_cast<char *>(&newDude), sizeof(Account));

		if( newDude.getAccNumb() != 0){//if it isn't a blank
			cout<<"What would you like your new name to be (up to 15 characters)\n>";
			cin>>b;//gets new name
			//sets account name as new name
			newDude.setName(b);
			//writes the Account to the file
			saveGame.seekp((a - 1) * sizeof(Account));
			saveGame.write(reinterpret_cast<char *>(&newDude), sizeof(Account));
			created = true;//exits loop
		}
		
		else{//it prints that the number is blank
			std::cerr<<"that number is blank"<<endl;
		}
	}
	return;
}

void AccCreator(std::fstream & saveGame){
	int a = 0;//stores account number
	string b;//stores new name
	bool created = false;//allows the loop to run
	Account newDude;//creates a blank Account
	printout(saveGame);//prints out the accounts that already exist
	while(created == false){
		a = 0;//sets a to 0
		while(a <= 0 || a > 100){//runs while a is less than 1 or greater than 500
			cout<<"What would you like your account number to be (1-100)(0 to exit)";
			a = get_move();//gets account number
			if (a == 0){
				return;
			}
			if(a < 0 || a > 100){//if a is equal to zero it returns out
				cout<<"Invalid Account Number"<<endl;//if it the same as the while condition it outputs that it is an invalid number
			}
		}

		saveGame.seekg((a - 1) * sizeof(Account));
		saveGame.read(reinterpret_cast<char *>(&newDude), sizeof(Account));

		if( newDude.getAccNumb() == 0){
			cout<<"What would you like your name to be (up to 15 characters)\n>";
			cin>>b;
			newDude.setAccNumb(a);
			newDude.setName(b);
			saveGame.seekp((a - 1) * sizeof(Account));
			saveGame.write(reinterpret_cast<char *>(&newDude), sizeof(Account));
			created = true;
		}
		
		else{
			std::cerr<<"that number is taken"<<endl;
			}//end first while loop
		}//end second while loop
	return;
}

void outputLine(Account & profile){//outputs the account into table format
	cout<<std::setw(3)<<profile.getAccNumb()<<"\t"<<std::setw(15)<<profile.getName()<<"\t"
	<<std::setw(3)<<profile.getWins()<<"\t"<<std::setw(3)<<profile.getLoss()<<"\t"<<std::setw(3)<<profile.getTies()<<endl;
}

void printout(std::fstream & file){//outputs file into table format
	Account test;//creates a Account to get information from the file
	int count = 1;//for outputting the accounts sequentially
	//outputs the headings of the table
	cout<<std::setw(7)<<"AccNumb\t"<<std::left<<std::setw(15)<<"Name"<<std::setw(3)<<"Wins\t"<<std::setw(3)<<"Losses\t"<<std::setw(3)<<"Ties"<<endl;
	//starts at the first account (slot 0)
	file.seekg(0);
	file.read(reinterpret_cast<char*>(&test), sizeof(Account));
	while(file.eof() != true){//runs as long as the file eof char isn't encountered
		if(test.getAccNumb() != 0){//tests if the account number is 0
			outputLine(test);//if it isn't then output test
		}
		//get the next account 
		file.seekg(count * sizeof(Account));
		file.read(reinterpret_cast<char*>(&test), sizeof(Account));
		count++;//count increments up
		
		if(count > 100){//incase the eof character is broken tests to see if count is greater than 500
			break;//break out of the loop
		}
	}
}

void printout_leaderboard(std::fstream & file){
	cout<<std::setw(7)<<"AccNumb\t"<<std::left<<std::setw(15)<<"Name"<<std::setw(3)<<"Wins\t"<<std::setw(3)<<"Losses\t"<<std::setw(3)<<"Ties"<<endl;
	Account test;
	int count = 1;
	int numb_of_Accounts = 0;
	while (count < 101){//finds the amount of valid accounts and assigns it to numb_of_Accounts
		file.seekg((count - 1) * sizeof(Account));
		file.read(reinterpret_cast<char*>(&test), sizeof(Account));
		if (test.getAccNumb() != 0){
			numb_of_Accounts += 1;
		}

		count++;
	}
	if(numb_of_Accounts == 0){
		cout<<"No winners"<<endl<<endl;
		return;
	}

	int * account_numbers = new int [numb_of_Accounts];//creates an array numb_of_Accounts long
	int position = 0;//position in above array
	Account foil;//for comparisons
	bool already_done = false;//prevents repeats

	for(int i = 0; i < numb_of_Accounts; i++){//sets them all elements to 0
		account_numbers[i] = 0;
	}
	count = 0;
	int count2 = 1;
	while(count < numb_of_Accounts){//prevents test from being a repeat

		count2 = 0;
		already_done = true;
		while(already_done == true){
			already_done = false;
			file.seekg(count2 * sizeof(Account));
			file.read(reinterpret_cast<char*>(&test), sizeof(Account));
			for(int i = 0; i < numb_of_Accounts; i++){//here to
				if(account_numbers[i] == test.getAccNumb()){
					already_done = true;
					i = numb_of_Accounts + 1;
				}
			}
			count2++;
		}
		
		count2 = 1;
		while(count2 < 101){//used to find the top players

			file.seekg(count2 * sizeof(Account));
			file.read(reinterpret_cast<char*>(&foil), sizeof(Account));

			if(foil.getAccNumb() == 0){//prevents account from being a 0 account
				count2 += 1;
				continue;
			}

			already_done = false;//to prevent any repeats
			for(int i = 0; i < numb_of_Accounts; i++){//here to
				if(account_numbers[i] == foil.getAccNumb()){
					already_done = true;
					i = numb_of_Accounts + 1;
				}
			}

			if(already_done == true){
				;
			}
			else if (test.getAccNumb() == 0){//incase test's number is 0
				test.setAccNumb(foil.getAccNumb());
				test.setWins(foil.getWins());
				test.setLoss(foil.getLoss());
				test.setTies(foil.getTies());
				test.setName(foil.getName());
			}
			else if (foil.getWins() < test.getWins()){//short circuits if less wins
				;
			}
			else if (foil.getWins() > test.getWins()){//short circuits if more wins
				test = foil;

			}
			else{//if equal
				if(foil.getLoss() < test.getLoss()){//finds out which one has more losses
					test = foil;
				}
				else if(foil.getLoss() == test.getLoss()){//if the losses are equal
					if(foil.getTies() < test.getTies()){//checks to see which has less ties
						test = foil;
					}
					else{//if equal or more ties
						;
					}
				}
				else{//if there are more loss
					;
				}
			}
			count2 += 1;
		}//end while loop 1


		if(test.getAccNumb() == 0){//another if it is 0 do not print
			;
		}
		else{
			outputLine(test);
			account_numbers[position] = test.getAccNumb();
			position++;
		}
		count++;
	}
	return;
}
