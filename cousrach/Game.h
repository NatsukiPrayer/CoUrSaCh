#pragma once
#include <algorithm>
#include <random>
#include <ctime>
#include "Player.h"

#ifndef  GAME_H
#define GAMER_H
using namespace std;

class Game {
	bool over;
	int winners;
	int dtrump;
	int turn;
	int defence;
	int num_of_players;
	int durak_p;
	Player** p;
public:
	void test_deck_clear();
	void restart();
	void game_start();
	void begin_turn();
	void change_turn_b();
	void change_turn_nb();
	void begin_turn_new();
	void end_turn();
	void add_phase();
	void beat_phase();
	void endgame();
	void info_p();
	void info_t();
	void info_global();
	int durak();
	vector <Card> deck;
	vector <Card> table;
	vector <Card> beatTable;
	vector <Card> beated;
};

#endif // ! GAME_H
