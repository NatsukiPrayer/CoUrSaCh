#pragma once
#include "Card.h"
#include <string>
#include <iostream>
#ifndef PLAYER_H
#define PLAYER_H
using namespace std;

class Player {
protected:
	string name;
	vector <Card> hand;
	bool turn;
	bool defence;
	bool win;
public:
	Player(string n, bool t, bool w, bool d);
	bool beat_ability(Card);
	bool add_ability(vector <Card>);
	virtual bool get_machine();
	virtual int card_pick(int);
	virtual int card_pick_to_beat(Card);
	virtual int card_pick_to_add(vector<Card>&, vector <Card>);
	virtual int card_play(std::vector<Card>&, int, int);
	void card_beat_add(std::vector<Card>&, int);
	void addCard(Card);
	vector <Card> get_hand();
	string get_name();
	bool get_turn();
	bool get_defence();
	bool get_win();
	Card get_card(int);
	string get_card_txt(Card);
	void set_turn();
	void set_defence();
	void set_win(vector <Card>);
	friend Card;
};

#endif // ! PLAYER_H

