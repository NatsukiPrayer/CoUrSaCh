#include "Player.h"

Player::Player(string n, bool t, bool w, bool d)
	: name(n), turn(t), win(w), defence(d)
{
}

bool Player::beat_ability(Card c)
{
	for (int i = 0; i < hand.size(); i++) {
		if (c.beat_con(hand.at(i)) == true)
			return true;
	}
	return false;
}

bool Player::add_ability(vector<Card> t_bt)
{
	for (int i = 0; i < t_bt.size(); i++) {
		for (int k = 0; k < hand.size(); k++) {
			if (hand.at(k).add_con(t_bt.at(i)) == true)
				return true;
		}
	}
	return false;
}

bool Player::get_machine()
{
	return false;
}

int Player::card_pick(int param) 												  													   
{											  // Param used to realized, are you
	int temp;							      // playing new card, or going to
	if (param == -1) {					      // use more then one card at once							  
		cout << "Choose a card to play:";	  // -1 - new, else - add another
		while (1) {							  // t - to
			cin >> temp;
			if (temp < 0 || temp > this->hand.size())
				cout << "Wrong card" << endl;
			else
				break;
		}
		return temp;
	}
	else {
		int temp;									 
		cout << "Choose a card to play:";
		while (1) {
			cin >> temp;
			if (temp < 0 || temp > this->hand.size() || hand.at(temp).get_rang() != param)
				cout << "You must add card with the same rang" << endl;
			else
				return temp;
		}
	}
}

int Player::card_pick_to_beat(Card beated)
{
	int c;
	cout << "Choose card to beat:";
	while (1) {
		cin >> c;
		if (beated.beat_con(hand.at(c)) == true)
			return c;
	}
}

int Player::card_pick_to_add(vector<Card>& t, vector <Card> bt)
{				
	bool stick = false;
	int temp;									 						      						  
		cout << "Choose a card to play:";		 
		while (1) {								 
			cin >> temp;						 
			if (temp < 0 || temp > this->hand.size())
				cout << "Wrong card" << endl;
			else {
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
			}
			if (stick == true)
				break;
		}
		return temp;
}

int Player::card_play(std::vector<Card>& t, int p, int r)
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
		cout << "Do you want to add another card?" << endl;
		cout << "1. Yes" << endl << "2. No" << endl;
		while (1) {
			cin >> answ;
			if (answ == 1) {
				return param+1;
			}
			else if (answ != 2)
				cout << "Try to enter correct answer";
			else
				break;
		}
	}
	return param;
}

void Player::card_beat_add(std::vector<Card>& t_bt, int p)
{
	vector <Card> ::iterator iter = hand.begin();
	t_bt.push_back(hand.at(p));
	iter += p;
	hand.erase(iter);
}

void Player::addCard(Card c)
{
	hand.push_back(c);
}


vector<Card> Player::get_hand()
{
	return hand;
}

string Player::get_name()
{
	return name;
}

bool Player::get_turn()
{
	return turn;
}

bool Player::get_defence()
{
	return defence;
}

bool Player::get_win()
{
	return win;
}

Card Player::get_card(int n)
{
	return hand.at(n);
}

string Player::get_card_txt(Card c)
{
	string suit;
	string rang;
	if (c.get_rang() == 0)
		rang = "six ";
	else if (c.get_rang() == 1)
		rang = "seven ";
	else if (c.get_rang() == 2)
		rang = "eight ";
	else if (c.get_rang() == 3)
		rang = "nine ";
	else if (c.get_rang() == 4)
		rang = "ten ";
	else if (c.get_rang() == 5)
		rang = "jack ";
	else if (c.get_rang() == 6)
		rang = "queen ";
	else if (c.get_rang() == 7)
		rang = "king ";
	else if (c.get_rang() == 8)
		rang = "ace ";
	if (c.get_suit() == 0)
		suit = "of hearts ";
	else if (c.get_suit() == 1)
		suit = "of diamonds ";
	else if (c.get_suit() == 2)
		suit = "of spades ";
	else if (c.get_suit() == 3)
		suit = "of trumps ";
	string fin = rang + suit;
	return fin;
}

void Player::set_turn()
{
	if (turn == true)
		turn = false;
	else
		turn = true;
}

void Player::set_defence()
{
	if (defence == true)
		defence = false;
	else
		defence = true;
}

void Player::set_win(vector<Card> d)
{
	if (d.size() == 0 && this->hand.size() == 0)
		win = true;
}
