#include "Human.h"

/*void Human::playCard(vector<Card>& tabl)
{
	Player::playCard(tabl);
	vector <Card> ::iterator iter = hand.begin();
	int i;
	int ii;
	int k;
	cout << "Choose a card to play:";
	while (1) {
		std::cin >> i;
		if (i > hand.capacity())
			cout << "Choose correct number";
		else
			break;
	}
	ii = hand.at(i).get_rang();
	iter += i;
	tabl.push_back(hand.at(i));
	hand.erase(iter);
	while (1) {
		vector <Card> ::iterator iter = hand.begin();
		bool more = false;
		for (int k = 0; k < hand.capacity(); k++) {
			if (hand.at(k).get_rang() == hand.at(i).get_rang() || k != i) {
				more = true;
			}
		}
		if (more == true) {
			cout << "Will you add another card?" << endl;
			string answ;
			cin >> answ;
			if (answ == "Will" || answ == "will" || answ == "Yes" || answ == "yes") {
				cout << "Choose a card to play:";
				while (1) {
					std::cin >> k;
					if (k > hand.capacity())
						cout << "Choose correct number";
					else {
						if (hand.at(k).get_rang() == ii) {
							iter += k;
							tabl.push_back(hand.at(k));
							hand.erase(iter);
							break;
						}
						else
							cout << "You can't add this card to the table";
					}	
				}
			}	
			else if (answ == "No" || answ == "no") {
				break;
			}
		}
	}
}*/

Human::Human(string n, bool t, bool w, bool d)
	:Player(n, t, w, d)
{
}
