/*
Connect4_player.h
@Project: ICS3UI
@Student: Richard Tu 
@Date: June 15 2016
**/

#ifndef CONNECT4_PLAYER_H_
#define CONNECT4_PLAYER_H_
#include<fstream>
#include"Connect4_file.h"

void who_won(int winner, Account & , Account & , std::fstream & );

void single_player(std::fstream & );

void multi_player(Account & , Account & , std::fstream & );

void identification(std::fstream & );

void file_stuff(std::fstream & );


#endif /* CONNECT4_PLAYER_H_ */
