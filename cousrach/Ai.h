#pragma once
#include "Player.h"
#ifndef  AI_H
#define AI_H

class Ai : public Player {
public:
	Ai(string, bool, bool, bool);
	bool get_machine();
	int card_play(std::vector<Card>&, int, int);
	int card_pick(int);
	int card_pick_to_beat(Card);
	int card_pick_to_add(vector<Card>&, vector <Card>);

};

#endif // ! AI_H
