#pragma once
#include <vector>
#include <string>
#ifndef  CARD_H
#define CARD_H

class Card {
	int rang;
	int suit;
	bool trump;
public:
	Card(int, int, bool);
	std::string get_card_txt();
	int get_rang();
	int get_suit();
	bool get_trump();
	
	void set_trump();
	bool beat_con(Card);
	bool add_con(Card);
};

#endif // ! CARD_H
