/*
Connect 4 main file
@Project: ICS3UI
@Student: Richard Tu 
@Date: June 15 2016
**/

#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include "Connect4_player.h"

using std::cout;
using std::cin;
using std::string;
using std::endl;


int main(){
	//creates a file object
	std::fstream file;
	file.open("accountsAndScore.txt");
	while(!file){
		if(!file){
			std::ofstream blank_file("accountsAndScore.txt", std::ios::out|std::ios::binary);
			blank_file.close();
			std::fstream blank_file2("accountsAndScore.txt", std::ios::out|std::ios::in|std::ios::binary);
			fileCreator(blank_file2);
		}
		file.open("accountsAndScore.txt");
	}

	//if there is no file then it will exit

	int selection = 1;//for your selection
	
	cout<<"This is a connect four program"<<endl;
	while (selection != 0){
		cout<<"(0) to exit\n(1) Single player\n(2) 2-player\n(3) File functions";//prints out your options
		selection = get_move();//gets your choice

		if (selection == 1){
			single_player(file);//runs single player
		}
		else if (selection == 2){
			identification(file);//runs multiplayer
		}
		else if (selection == 3){
			file_stuff(file);//allows you to edit file
		}

		else if (selection == 0){
			;//does nothing thus exits
		}
		else{
			cout<<"Not a valid input"<<endl;
		}
	}
}

