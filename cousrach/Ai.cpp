#include "Ai.h"

int Ai::card_play(std::vector<Card>& t, int p, int r)
{
	int answ;
	int param;
	bool stick = false;
	for (int i = 0; i < hand.size(); i++) {
		if (hand.at(i).get_rang() == r && i != p) {
			stick = true;
			param = r;
			break;
		}
	}
	param = r * 10;
	vector <Card> ::iterator iter = hand.begin();
	t.push_back(hand.at(p));
	iter += p;
	hand.erase(iter);
	if (stick == true) {
		while (1) {
			answ = rand() % 2;
			if (answ == 0) {
				return param + 1;
			}
			else
				break;
		}
	}
	return param;
}
int Ai::card_pick(int param)
{			
	int temp = 0;							      
	if (param == -1) {					      							  
		temp = rand() % this->hand.size();
		return temp;
	}
	else { 
			while (1) {
				temp = rand() % this->hand.size();
				if (hand.at(temp).get_rang() == param)
					break;
			}
			return temp;
		}
}

int Ai::card_pick_to_beat(Card beated)
{
	int c;
	while (1) {
		c = rand() % hand.size();
		if (beated.beat_con(hand.at(c)) == true)
			return c;
	}
}

int Ai::card_pick_to_add(vector<Card>& t, vector<Card> bt)
{
	bool stick = false;
	int temp;
	while (1) {
		temp = rand()%hand.size();
			for (int i = 0; i < t.size(); i++) {
				if (hand.at(temp).get_rang() == t.at(i).get_rang()) {
					stick = true;
					break;
				}
			}
			if (stick == false) {
				for (int i = 0; i < bt.size(); i++) {
					if (hand.at(temp).get_rang() == bt.at(i).get_rang()) {
						stick = true;
						break;
					}
				}
			}
		if (stick == true)
			break;
	}
	return temp;
}


Ai::Ai(string n, bool t, bool w, bool d)
	:Player(n, t, w, d)
{
}

bool Ai::get_machine()
{
	return true;
}
