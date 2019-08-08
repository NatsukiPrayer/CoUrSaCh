#include "Game.h"
#include "Ai.h"
#include "Human.h"
#include <iomanip>
#include <iterator>

void Game::test_deck_clear()
{
	deck.clear();
}

void Game::restart()
{
	int tr;
	cout << "Would you like to try again?" << endl
		<< "1. Yes " << endl << "2. No " << endl;
	cin >> tr;
	while (1) {
		if (tr == 1)
		{
			return(this->game_start());
		}

		else if (tr == 2)
			return(exit(0));
		else
			cout << "Enter your answer like 1 or 2" << endl;
	}
}

void Game::game_start()
{
	srand(time(NULL));
	over = false;
	winners = 0;
	durak_p = -1;
	dtrump = -1;
	turn = -1;
	num_of_players = -1;
	p = nullptr;

	vector <string> omni = { "Jhon", "Carl", "Jack", "Genji", "Ivan", "Rough", "Gabe",
							"Dobro", "Henry", "Sam", "Harlampii", "Orochimaru" };
	vector <string> dialog = { "Hey, will you answer my question?", "C'mon, don't sleep",
							"I am talking with you, mr Sleepy one", "Feeling like I'm talking with a wall"
							, "I see you don't like to talk, don't you?" };
	string temp;
	int abs_min = 10;
	int answ;
	int first=0;
	int lim = 0;

	cout << "Choose your name:";
	cin >> temp;
	cout << "num_of_players";
	cin >> num_of_players;

	int* min = new int[num_of_players];
	for (int i = 0; i < num_of_players; i++)
		min[i] = 10;

	p = new Player * [num_of_players];
	p[0] = new Human (temp, false, false, false);;
	for (int i = 1; i < num_of_players; i++)
		p[i] = new Ai((omni.at(rand() % 11)), false, false, false);
	for (int i = 0; i < 4; i++) {
		for (int k = 0; k < 9; k++) {
			deck.push_back(Card(k, i, false));
		}
	}
	while (1) {
		auto rng = default_random_engine{};
		for (int i=0; i < rand() % 5 +2; i++)
			shuffle(std::begin(this->deck), std::end(this->deck), rng);
		cout << "Shuffle one more time or should we begin?" << endl;
		cin >> temp;
		if ( temp == "more" || temp == "yes" || temp == "Yes" 
			|| temp == "Shuffle" || temp == "shuffle" || temp == "More") {
			shuffle(std::begin(this->deck), std::end(this->deck), rng);
		}
		else if (temp == "No" || temp == "no" || temp == "Begin" || temp == "begin") {
				dtrump = deck.at(0).get_suit();
			for (int i = 0; i < 36; i++) {
				if (deck.at(0).get_suit() == deck.at(i).get_suit())
					deck.at(i).set_trump();
			}
			cout << "trump is ";
			if (dtrump == 0)
				cout << "heart. ";
			else if (dtrump == 1)
				cout << "diamond. ";
			else if (dtrump == 2)
				cout << "spade. ";
			else if (dtrump == 3)
				cout << "club. ";
			break;
		}
		else
			cout << "Answer clearer next time" << endl;
	}
	for (int i = 0; i < num_of_players * 6; i++) {
		vector <Card> ::iterator iter = deck.begin();
		p[i % num_of_players]->addCard(deck.at(0));
		deck.erase(iter);
	}
		for (int k = 1; k <= num_of_players - 1; k++) {
			for (int c = 0; c < 6; c++) {
				if (c ==0 && p[k]->get_card(c).get_trump() == true)
					min[k] = p[k]->get_card(c).get_rang();
				else if ( min[k] > p[k]->get_card(c).get_rang() && p[k]->get_card(c).get_trump() == true)
					min[k] = p[k]->get_card(c).get_rang();
			}
		}
	for (int i = 1; i <= num_of_players - 1; i++) {
		if (abs_min > min[i]) {
			abs_min = min[i];
			first = i;
		}
	}
	cout << "What do you have?" << endl;
	cout << "1. bluff " << endl;
	cout << "2. fair game " << endl;
	cin >> answ;
	while (1) {
		if (answ != 1 && answ != 2) {
			if (lim < 4) {
				cout << "You're choose to ignore the game " << endl;
				cout << dialog.at(rand() % 4) << endl;
				lim += 1;
			}
			else {
				cout << "-We're done, look for someone else to play!" << endl;
				cout << "Omnics stood up and got out of the bar, lefting you alone at the table" << endl;
				restart();
				exit(1);
			}
		}
		else
			break;
	}
		if (answ == 1) {
			cout << "You said:" << endl;
			cout << "-I have the lowest trump among you" << endl;
			int luck;
			luck = rand() % 4;
			if (luck < 4) {
				cout << "Omnics got you bluffing" << endl;
				cout << "-We're done, look for someone else to play!" << endl;
				cout << "Omnics stood up and got out of the bar, lefting you alone at the table" << endl;
				restart();
			}
			else {
				p[0]->set_turn();
				p[1]->set_defence();
			}
				
		}
		else if (answ == 2) {
			bool stick = false;
			for (int i = 0; i < 6; i++) {
				if (p[0]->get_card(i).get_rang() < abs_min) {
					cout << "You have the lowest trump among other, game will start from your turn" << endl;
					p[0]->set_turn();
					p[1]->set_defence();
					first = 0;
					stick = true;
					break;
				}
			}
			if (stick == false) {
				cout << "You don't have a lower trump, game will start from ";
				cout << p[first]->get_name() << endl;
				p[first]->set_turn();
				p[(first + 1) % num_of_players]->set_defence();
			}
		}
		turn = first;
		defence = (first + 1) % num_of_players;
		return(this->begin_turn_new());
}

void Game::begin_turn()
{
	durak_p = -1;
	while (1707) {
		if (this->durak() == 0 || this->durak() == 1)
			break;
		int ts = table.size();
		int bts = beatTable.size();
		this->info_global();
		bool stick777 = true;
		bool stick778 = false;
		bool stick = false;
		int answw = -1;
		int rang = -1;
		int position = -1;
		int huint = -1;
		int help = 0;
		int i = 0;
		int add_ab_help = 0;
		while (1) {
			if (p[i % num_of_players]->get_turn() != true)
				i += 1;
			else
				break;
		}
		while (1) {
			this->info_global();
			position = p[i % num_of_players]->card_pick(rang);
			huint = p[i % num_of_players]->get_card(position).get_rang();
			this->info_global();
			rang = p[i % num_of_players]->card_play(table, position, huint);
			if (rang % 10 == 0)
				break;
			rang = rang / 10;
		}
		this->info_global();
		turn = i % num_of_players;
		for (int l = beatTable.size(); l < table.size(); l++) {
			if (p[(i + 1) % num_of_players]->beat_ability(table.at(l)) == true && p[(i + 1) % num_of_players]->get_win() == false) {
				p[(i + 1) % num_of_players]->card_beat_add(beatTable, p[(i + 1) % num_of_players]->card_pick_to_beat(table.at(l)));
				p[(i + 1) % num_of_players]->set_win(deck);
				this->info_global();
				system("pause");
			}
			else if (p[(i + 1) % num_of_players]->get_win() == false) {
				if (p[(i + 1) % num_of_players]->get_machine() == true) {
					cout << "Omnic is taking the card" << endl;
					system("pause");
					ts = table.size();
					bts = beatTable.size();
					for (int h = 0; h < ts; h++) {
						p[(i + 1) % num_of_players]->addCard(table.at(0));
						vector <Card> ::iterator iter = table.begin();
						table.erase(iter);
						this->info_global();
					}
					for (int g = 0; g < bts; g++) {
						p[(i + 1) % num_of_players]->addCard(beatTable.at(0));
						vector <Card> ::iterator iter = beatTable.begin();
						beatTable.erase(iter);
						this->info_global();
					}
					p[turn]->set_turn();
					p[(i + 1) % num_of_players]->set_defence();
					p[(i + 2) % num_of_players]->set_turn();
					p[(i + 3) % num_of_players]->set_defence();
					stick778 = true;
				}
				else {
					cout << "You have nothing to beat it" << endl;
					system("pause");
					ts = table.size();
					bts = beatTable.size();
					for (int h = 0; h < ts; h++) {
						p[(i + 1) % num_of_players]->addCard(table.at(0));
						vector <Card> ::iterator iter = table.begin();
						table.erase(iter);
						this->info_global();
					}
					for (int g = 0; g < bts; g++) {
						p[(i + 1) % num_of_players]->addCard(beatTable.at(0));
						vector <Card> ::iterator iter = beatTable.begin();
						beatTable.erase(iter);
						this->info_global();
					}
					p[turn]->set_turn();
					p[(i + 1) % num_of_players]->set_defence();
					p[(i + 2) % num_of_players]->set_turn();
					p[(i + 3) % num_of_players]->set_defence();
					stick778 = true;
				}
			}
			else if (p[(i + 1) % num_of_players]->get_win() == true) {
				p[(i + 1) % num_of_players]->set_defence();
				p[(i + 2) % num_of_players]->set_defence();
				stick778 = true;
			}
		}
		if (stick778 == false) {
			while (p[turn]->get_turn() == true) {
				this->info_global();
				bool ai_add_ability = false;
				bool human_add_ability = false;
				for (int y = 0; y < num_of_players; y++)
					if ((p[y]->add_ability(table) == true || p[y]->add_ability(beatTable) == true) && p[y]->get_defence() != true) {
						if (p[y]->get_machine() == false)
							human_add_ability = true;
						else {
							ai_add_ability = true;
							break;
						}
					}
					for (int k = (i % num_of_players); k < num_of_players && table.size() != 6 &&(human_add_ability==true || ai_add_ability==true); k = (k+1)%num_of_players) { // TUTA
						if ((p[k]->add_ability(table) == true || p[k]->add_ability(beatTable) == true) && table.size() != 6 && p[k]->get_defence() != true) {
							if (p[k]->get_machine() == true && p[k]->get_defence() != true && ai_add_ability == true) {
								p[k]->card_beat_add(table, p[k]->card_pick_to_add(table, beatTable));
								this->info_global();
								system("pause");
							}
							else if (human_add_ability == true ) {
								cout << endl << "Do you want to add card to the table?" << endl
									<< "1. Yes" << endl << "2. No" << endl;
								while (1) {
									cin >> answw;
									if (answw != 1 && answw != 2)
										cout << "Choose correctly next time" << endl;
									else if (answw == 1) {
										p[0]->card_beat_add(table, p[0]->card_pick_to_add(table, beatTable));
										this->info_global();
										system("pause");
										break;
									}
									else if (answw == 2) {
										human_add_ability = false;
										break;
									}
								}
							}
						}
						if (ai_add_ability == true || human_add_ability == true) {
							for (int y = 0; y < num_of_players; y++)
								if ((p[y]->add_ability(table) == false && p[y]->add_ability(beatTable) == false) && p[y]->get_defence() != true) {
									if (p[y]->get_machine() == false)
										human_add_ability = false;
									else {
										add_ab_help += 1;
									}
									if (add_ab_help == num_of_players - 1)
										ai_add_ability == false;
								}
					}
				}
				for (int h = beatTable.size(); h < table.size(); h++) {
					if (p[(i + 1) % num_of_players]->beat_ability(table.at(h)) == true && p[(i + 1) % num_of_players]->get_win() == false) {
						if (p[(i + 1) % num_of_players]->get_machine() == false) {
							cout << "Will you beat or take?" << endl
								<< "1. Yes" << endl << "2. No" << endl;
							while (1) {
								cin >> answw;
								if (answw != 1 && answw != 2)
									cout << "Choose correctly next time" << endl;
								else if (answw == 1) {
									break;
								}
								else if (answw == 2) {
									cout << "You taking the cards" << endl;
									system("pause");
									for (int i = 0; i < ts; i++) {
										p[(i + 1) % num_of_players]->addCard(table.at(0));
										vector <Card> ::iterator iter = table.begin();
										table.erase(iter);
										this->info_global();
										system("pause");
									}
									for (int g = 0; g < bts; g++) {
										p[(i + 1) % num_of_players]->addCard(beatTable.at(0));
										vector <Card> ::iterator iter = beatTable.begin();
										beatTable.erase(iter);
										this->info_global();
										system("pause");
									}
									p[turn]->set_turn();
									p[(i + 1) % num_of_players]->set_defence();
									p[(i + 2) % num_of_players]->set_turn();
									p[(i + 3) % num_of_players]->set_defence();
									stick777 = true;
									break;
								}
							}
							if (stick777 == true)
								break;
						}
						p[(i + 1) % num_of_players]->card_beat_add(beatTable, p[(i + 1) % num_of_players]->card_pick_to_beat(table.at(h)));
						p[(i + 1) % num_of_players]->set_win(deck);
						system("pause");
					}
					else {
						int ts = table.size();
						int bts = beatTable.size();
						if (p[(i + 1) % num_of_players]->get_machine() == true) {
							cout << "Omnic is taking the cards" << endl;
							system("pause");
							for (int i = 0; i < ts; i++) {
								p[(i + 1) % num_of_players]->addCard(table.at(0));
								vector <Card> ::iterator iter = table.begin();
								table.erase(iter);
								this->info_global();
							}
							for (int g = 0; g < bts; g++) {
								p[(i + 1) % num_of_players]->addCard(beatTable.at(0));
								vector <Card> ::iterator iter = beatTable.begin();
								beatTable.erase(iter);
								this->info_global();
								system("pause");
							}
							p[turn]->set_turn();
							p[(i + 1) % num_of_players]->set_defence();
							p[(i + 2) % num_of_players]->set_turn();
							p[(i + 3) % num_of_players]->set_defence();
							stick777 = true;
							break;
						}
						else {
							cout << "You have nothing to beat it" << endl;
							system("pause");
							for (int i = 0; i < ts; i++) {
								p[(i + 1) % num_of_players]->addCard(table.at(0));
								vector <Card> ::iterator iter = table.begin();
								table.erase(iter);
								this->info_global();
								system("pause");
							}
							for (int g = 0; g < bts; g++) {
								p[(i + 1) % num_of_players]->addCard(beatTable.at(0));
								vector <Card> ::iterator iter = beatTable.begin();
								beatTable.erase(iter);
								this->info_global();
								system("pause");
							}
							p[turn]->set_turn();
							p[(i + 1) % num_of_players]->set_defence();
							p[(i + 2) % num_of_players]->set_turn();
							p[(i + 3) % num_of_players]->set_defence();
							stick777 = true;
							break;
						}
					}
					system("pause");
				}
				if (stick777 == true)
					break;
				if (ai_add_ability == false && table.size() == beatTable.size() && human_add_ability == false) {
					ts = table.size();
					bts = beatTable.size();
					for (int n = 0; n < ts; n++) {
						beated.push_back(table.at(0));
						vector <Card> ::iterator iter = table.begin();
						table.erase(iter);
						this->info_global();
					}
					for (int g = 0; g < bts; g++) {
						beated.push_back(beatTable.at(0));
						vector <Card> ::iterator iter = beatTable.begin();
						beatTable.erase(iter);
						this->info_global();
					}
					p[turn]->set_turn();
					p[(i + 1) % num_of_players]->set_turn();
					p[(i + 1) % num_of_players]->set_defence();
					p[(i + 2) % num_of_players]->set_defence();
					break;
				}
			}
		}
		for (int f = 0; f < num_of_players; f++) {
			while (p[f]->get_hand().size() < 6 && deck.size() != 0) {
				p[f]->addCard(deck.at(0));
				vector <Card> ::iterator iter = deck.begin();
				deck.erase(iter);
				this->info_global();
			}
		}
		ts = table.size();
		bts = beatTable.size();
		for (int n = 0; n < ts; n++) {
			beated.push_back(table.at(0));
			vector <Card> ::iterator iter = table.begin();
			table.erase(iter);
			this->info_global();
		}
		for (int g = 0; g < bts; g++) {
			beated.push_back(beatTable.at(0));
			vector <Card> ::iterator iter = beatTable.begin();
			beatTable.erase(iter);
			this->info_global();
		}
		if (stick778 == false) {
			p[turn]->set_turn();
			p[(i + 1) % num_of_players]->set_turn();
			p[(i + 1) % num_of_players]->set_defence();
			p[(i + 2) % num_of_players]->set_defence();
		}
		system("pause");
		while (1) {
			if (p[i % num_of_players]->get_turn() != true)
				i += 1;
			else
				break;
		}
		turn = i % num_of_players;
		this->info_global();

	}
}

void Game::change_turn_b()
{
	p[turn]->set_turn();
	for (int i=0; i<num_of_players; i++)
		if (p[i]->get_defence() == true) {
			p[i]->set_defence();
			p[i]->set_turn();
			turn = i;
			for (int k=i; k<num_of_players; k = (k + 1) % num_of_players)
				if (p[k]->get_win() != true && k!=i) {
					p[k]->set_defence();
					defence = k;
					return;
				}
		}
}

void Game::change_turn_nb()
{
	p[turn]->set_turn();
	for (int i = 0; i <num_of_players; i++)
		if (p[i]->get_defence() == true) {
			p[i]->set_defence();
			for (int k = i; k < num_of_players; k=(k+1)%num_of_players)
				if (p[k]->get_win() != true && k!=i) {
					p[k]->set_turn();
					turn = k;
						for (int l = k; l < num_of_players; l=(l+1)%num_of_players)
							if (p[l]->get_win() != true && l!=k) {
								p[l]->set_defence();
								defence = l;
								return;
							}	
				}
		}
}

void Game::begin_turn_new()
{
	if (this->durak() == 0)
		return(this->endgame());
	if (this->durak() == 1)
		return(this->endgame());
		this->info_global();
		int ts = table.size();
		int bts = beatTable.size();
		this->info_global();
		int answw = -1;
		int rang = -1;
		int position = -1;
		int huint = -1;
		int help = 0;
		while (1) {
			this->info_global();
			position = p[turn]->card_pick(rang);
			huint = p[turn]->get_card(position).get_rang();
			this->info_global();
			rang = p[turn]->card_play(table, position, huint);
			if (rang % 10 == 0)
				break;
			rang = rang / 10;
		}
		this->info_global();
		// turn = i % num_of_players;
		for (int l = beatTable.size(); l < table.size(); l++) {
			if (p[defence]->beat_ability(table.at(l)) == true && p[defence]->get_win() == false) {
				if (p[defence]->get_machine() == true) {
					p[defence]->card_beat_add(beatTable, p[defence]->card_pick_to_beat(table.at(l)));
					p[defence]->set_win(deck);
					this->info_global();
					system("pause");
				}
				else {
					cout << "Will you beat or take?" << endl
						<< "1.Beat" << endl << "2.Take" << endl;
					while (1) {
						cin >> answw;
						if (answw != 1 && answw != 2)
							cout << "Choose correctly next time" << endl;
						else if (answw == 1) {
							p[defence]->card_beat_add(beatTable, p[defence]->card_pick_to_beat(table.at(l)));
							p[defence]->set_win(deck);
							system("pause");
							break;
						}
						else if (answw == 2) {
							cout << "You taking the cards" << endl;
							ts = table.size();
							bts = beatTable.size();
							system("pause");
							for (int i = 0; i < ts; i++) {
								p[defence]->addCard(table.at(0));
								vector <Card> ::iterator iter = table.begin();
								table.erase(iter);
								this->info_global();
								system("pause");
							}
							for (int g = 0; g < bts; g++) {
								p[defence]->addCard(beatTable.at(0));
								vector <Card> ::iterator iter = beatTable.begin();
								beatTable.erase(iter);
								this->info_global();
								system("pause");
							}
							this->change_turn_nb();
							return(this->end_turn());
						}
					}
				}
			}
			else if (p[defence]->get_win() == false) {
				if (p[defence]->get_machine() == true) {
					cout << "Omnic is taking the card" << endl;
					system("pause");
					ts = table.size();
					bts = beatTable.size();
					for (int h = 0; h < ts; h++) {
						p[defence]->addCard(table.at(0));
						vector <Card> ::iterator iter = table.begin();
						table.erase(iter);
						this->info_global();
					}
					for (int g = 0; g < bts; g++) {
						p[defence]->addCard(beatTable.at(0));
						vector <Card> ::iterator iter = beatTable.begin();
						beatTable.erase(iter);
						this->info_global();
					}
					this->change_turn_nb();
					return(this->end_turn());
				}
				else {
					cout << "You have nothing to beat it" << endl;
					system("pause");
					ts = table.size();
					bts = beatTable.size();
					for (int h = 0; h < ts; h++) {
						p[defence]->addCard(table.at(0));
						vector <Card> ::iterator iter = table.begin();
						table.erase(iter);
						this->info_global();
					}
					for (int g = 0; g < bts; g++) {
						p[defence]->addCard(beatTable.at(0));
						vector <Card> ::iterator iter = beatTable.begin();
						beatTable.erase(iter);
						this->info_global();
					}
					this->change_turn_nb();
					return(this->end_turn());
				}
			}
		}
		return(this->add_phase());
}

void Game::add_phase()
{
	int temp = 0;
	int temp1 = 0;
	int answ = -1;
	this->info_global();
	bool ai_add_ability = false;
	bool human_add_ability = false;
	for (int y = 0; y < num_of_players; y++)
		if ((p[y]->add_ability(table) == true || p[y]->add_ability(beatTable) == true) && p[y]->get_defence() != true && p[y]->get_win() != true) {
			if (p[y]->get_machine() == false)
				human_add_ability = true;
			else {
				ai_add_ability = true;
				break;
			}
		}
	for (int k = turn; table.size() != 6 && (human_add_ability == true || ai_add_ability == true); k = (k + 1) % num_of_players) { // TUTA
		if ((p[0]->add_ability(table) == true || p[0]->add_ability(beatTable) == true) && p[0]->get_defence() != true && p[0]->get_win() != true)
			human_add_ability = true;
		if ((p[k]->add_ability(table) == true || p[k]->add_ability(beatTable) == true) && p[k]->get_defence() != true && p[k]->get_win() != true) {
			if (p[k]->get_machine() == true ) {
				p[k]->card_beat_add(table, p[k]->card_pick_to_add(table, beatTable));
				this->info_global(); 
				cout << endl << p[k]->get_name() << " add cards " << endl;
				system("pause");
			}
			else if (human_add_ability == true) {
				cout << endl << "Do you want to add card to the table?" << endl
					<< "1. Yes" << endl << "2. No" << endl;
				while (1) {
					cin >> answ;
					if (answ != 1 && answ != 2)
						cout << "Choose correctly next time" << endl;
					else if (answ == 1) {
						p[0]->card_beat_add(table, p[0]->card_pick_to_add(table, beatTable));
						this->info_global();
						system("pause");
						if ((p[0]->add_ability(table) == false && p[0]->add_ability(beatTable) == false))
							human_add_ability = false;
						break;
					}
					else if (answ == 2) {
						human_add_ability = false;
						break;
					}
				}
			}
		}
		temp = 0;
		for (int y = 0; y < num_of_players; y++)
			if (p[y]->get_win() == true && p[y]->get_machine() == true)
				temp1 += 1;
		for (int y = 0; y < num_of_players; y++)
			if ((p[y]->add_ability(table) == false && p[y]->add_ability(beatTable) == false))
				if (p[y]->get_machine() == true)
					temp += 1;
		if (temp = num_of_players - 1 - temp1)
			ai_add_ability = false;
	}
	if (table.size() == beatTable.size()) {
		this->change_turn_b();
		return(this->end_turn());
	}
	else
		return(this->beat_phase());
}

void Game::beat_phase()
{
	this->info_global();
	int answ = -1;
	for (int h = beatTable.size(); h < table.size(); h++) {
		int ts = table.size();
		int bts = beatTable.size();
		if (p[defence]->beat_ability(table.at(h)) == true) {
			if (p[defence]->get_machine() == false) {
				cout << "Will you beat or take?" << endl
					<< "1.Beat" << endl << "2.Take" << endl;
				while (1) {
					cin >> answ;
					if (answ != 1 && answ != 2)
						cout << "Choose correctly next time" << endl;
					else if (answ == 1) {
						p[defence]->card_beat_add(beatTable, p[defence]->card_pick_to_beat(table.at(h)));
						p[defence]->set_win(deck);
						system("pause");
						break;
					}
					else if (answ == 2) {
						cout << "You taking the cards" << endl;
						system("pause");
						for (int i = 0; i < ts; i++) {
							p[defence]->addCard(table.at(0));
							vector <Card> ::iterator iter = table.begin();
							table.erase(iter);
							this->info_global();
							system("pause");
						}
						for (int g = 0; g < bts; g++) {
							p[defence]->addCard(beatTable.at(0));
							vector <Card> ::iterator iter = beatTable.begin();
							beatTable.erase(iter);
							this->info_global();
							system("pause");
						}
						this->change_turn_nb();
						return(this->end_turn());
					}
				}
			}
			else {
				p[defence]->card_beat_add(beatTable, p[defence]->card_pick_to_beat(table.at(h)));
				p[defence]->set_win(deck);
				system("pause");
			}
		}
		else {
			if (p[defence]->get_machine() == true) {
				cout << "Omnic is taking the cards" << endl;
				system("pause");
				for (int i = 0; i < ts; i++) {
					p[defence]->addCard(table.at(0));
					vector <Card> ::iterator iter = table.begin();
					table.erase(iter);
					this->info_global();
				}
				for (int g = 0; g < bts; g++) {
					p[defence]->addCard(beatTable.at(0));
					vector <Card> ::iterator iter = beatTable.begin();
					beatTable.erase(iter);
					this->info_global();
					system("pause");
				}
				this->change_turn_nb();
				return(this->begin_turn_new());
			}
			else {
				cout << "You have nothing to beat it" << endl;
				system("pause");
				for (int i = 0; i < ts; i++) {
					p[(i + 1) % num_of_players]->addCard(table.at(0));
					vector <Card> ::iterator iter = table.begin();
					table.erase(iter);
					this->info_global();
					system("pause");
				}
				for (int g = 0; g < bts; g++) {
					p[defence]->addCard(beatTable.at(0));
					vector <Card> ::iterator iter = beatTable.begin();
					beatTable.erase(iter);
					this->info_global();
					system("pause");
				}
				this->change_turn_nb();
				return(this->end_turn());
			}
		}
	}
	return(this->add_phase());
}

void Game::endgame()
{
	cout << "Durak is " << p[durak_p]->get_name() << endl;
	system("pause");
	exit(0);
}


void Game::info_p()
{
	//int y;
	//cin >> y;
	system("cls");
	cout << "Trump is ";
	if (dtrump == 0)
		cout << "heart";
	else if (dtrump == 1)
		cout << "diamond ";
	else if (dtrump == 2)
		cout << "spade ";
	else if (dtrump == 3)
		cout << "club ";
	cout << "||||||| now is player's " << turn << " turn |||||||"
		<< " there are " << deck.size() << " cards at the deck " << endl;
	for (int i = 0; i < 85; i++)
		cout << "=";
	cout << endl;
	cout << "Your cards:                     Players:" << endl;
	for (int i = 0; i < num_of_players; i++) {
		if (i < p[0]->get_hand().size()) {
			cout << i << ". " << p[0]->get_card_txt(p[0]->get_card(i))
				<< setw(30 - p[0]->get_card_txt(p[0]->get_card(i)).length())
				<< i << ". " << p[i]->get_name();
			if (p[i]->get_turn() == true)
				cout << "(his turn)";
		}
		else {
			cout << setw(30)
				<< i << ". " << p[i]->get_name();
			if (p[i]->get_turn() == true)
				cout << "(his turn)";
		}
		cout << endl;
	}
	for (int k = num_of_players; k < p[0]->get_hand().size(); k++)
		cout << k << ". " << p[0]->get_card_txt(p[0]->get_card(k)) << endl;
}

void Game::info_t()
{
	for (int i = 0; i < 85; i++)
		cout << "=";
	cout << endl;
	int k = 0;
	for (int i = 0; i < table.size(); i++) {
		cout << i << ". " << table.at(i).get_card_txt();
		if(beatTable.size() > 0 && k<beatTable.size())
			cout << "beated with " << beatTable.at(i).get_card_txt();
		cout << endl;
		k += 1;
	}
}

void Game::info_global()
{
	this->info_p();
	this->info_t();
}

int Game::durak()
{
	int t = 0;
	for (int u = 0; u < num_of_players; u++)
		if (p[u]->get_win() == true)
			t++;
	if (t == num_of_players - 1) {  // durak
		for (int u = 0; u < num_of_players; u++)
			if (p[u]->get_win() == false)
				durak_p = u;
		return 0;
	}
	else if (t == num_of_players) { // draw
		for (int u = 0; u < num_of_players; u++)
			if (p[u]->get_win() == false)
				durak_p = u;
		return 1;
	}
	else                          // still playing
		return 2; 
}

void Game::end_turn()
{
	for (int u = 0; u < num_of_players; u++)
		p[u]->set_win(deck);
	if (this->durak() == 0)
		return(this->endgame());
	if (this->durak() == 1)
		return(this->endgame());
		int ts = table.size();
		int bts = beatTable.size();
		for (int n = 0; n < ts; n++) {
			beated.push_back(table.at(0));
			vector <Card> ::iterator iter = table.begin();
			table.erase(iter);
			this->info_global();
		}
		for (int g = 0; g < bts; g++) {
			beated.push_back(beatTable.at(0));
			vector <Card> ::iterator iter = beatTable.begin();
			beatTable.erase(iter);
			this->info_global();
		}
		for (int f = 0; f < num_of_players; f++) {
			while (p[f]->get_hand().size() < 6 && deck.size() != 0) {
				p[f]->addCard(deck.at(0));
				vector <Card> ::iterator iter = deck.begin();
				deck.erase(iter);
				this->info_global();
			}
		}
		system("pause");
		this->info_global();
		return(this->begin_turn_new());
}
