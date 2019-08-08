#include "Card.h"

Card::Card(int r, int s, bool t)
	:rang(r), suit(s), trump(t)
{}

std::string Card::get_card_txt()
{
	std::string suit;
	std::string rang;
	if (this -> rang == 0)
		rang = "six ";
	else if (this->rang == 1)
		rang = "seven ";
	else if (this->rang == 2)
		rang = "eight ";
	else if (this->rang == 3)
		rang = "nine ";
	else if (this->rang == 4)
		rang = "ten ";
	else if (this->rang == 5)
		rang = "jack ";
	else if (this->rang == 6)
		rang = "queen ";
	else if (this->rang == 7)
		rang = "king ";
	else if (this->rang == 8)
		rang = "ace ";
	if (this -> suit == 0)
		suit = "of hearts ";
	else if (this->suit == 1)
		suit = "of diamonds ";
	else if (this->suit == 2)
		suit = "of spades ";
	else if (this->suit == 3)
		suit = "of trumps ";
	std::string fin = rang + suit;
	return fin;
}

int Card::get_rang()
{
	return rang;
}

int Card::get_suit()
{
	return suit;
}

bool Card::get_trump()
{
	return trump;
}

void Card::set_trump()
{
	this->trump = true;
}

bool Card::beat_con(Card attack)
{
	if (this->suit == attack.suit ) {
		if (this->rang > attack.rang )
			return false;
		else {
			return true;
		}
	}
	else if (attack.trump == true) 
		return true;
	return false;
}

bool Card::add_con(Card c)
{
	if (this->rang == c.rang)
		return true;
	else
		return false;
}
