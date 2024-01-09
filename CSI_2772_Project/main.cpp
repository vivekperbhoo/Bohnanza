#include "Card.h"
#include "Deck.h"
#include "CardFactory.h"
#include "Player.h"
#include "Table.h"
#include "Chain.h"
#include "Hand.h"
#include "DiscardPile.h"
#include "TradeArea.h"
#include "Chain_Base.h"
#include "NotEnoughCoinsException.h"
#include "IllegalTypeException.h"
#include <iostream>
#include <string.h>

int main() {
	std::string reload;
	std::cout << "Would you like to reload the game from saved file?(y/n): ";
	std::cin >> reload;
	Player* player1;
	Player* player2;
	DiscardPile discardPile;
	TradeArea tradeArea;
	Deck deck;
	Table table;

	if (reload=="y") {

		const CardFactory* cf = CardFactory::getFactory();
		std::ifstream player1File("Player1.txt");
		player1 = new Player(player1File, cf);

		std::ifstream player2File("Player2.txt");
		player2 = new Player(player2File, cf);

		std::ifstream hand1File("Hand1.txt");
		Hand hand1 = Hand(hand1File, cf);

		player1->setHand(hand1);

		std::ifstream hand2File("Hand2.txt");
		Hand hand2 = Hand(hand2File, cf);

		player2->setHand(hand2);

		std::ifstream discardPileFile("DiscardPile.txt");
		discardPile = DiscardPile(discardPileFile, cf);

		std::ifstream tradeAreaFile("TradeArea.txt");
		tradeArea = TradeArea(tradeAreaFile, cf);

		std::ifstream deckFile("Deck.txt");
		deck = Deck(deckFile, cf);

		table = Table(*player1, *player2, deck, discardPile, tradeArea);
		std::cout << "Player1 hand: ";
		(player1->getHand()).displayHand();
		std::cout << "Player2 hand: ";
		(player2->getHand()).displayHand();
		std::cout << "trade area: ";
		tradeArea.displayTradeArea();
		std::cout << "Table: ";
		table.displayTable();
		std::cout << "Discard pile: ";
		discardPile.display();
		
	}
	else {
		//getting singleton instance and initialising deck
		CardFactory* cf = CardFactory::getFactory();

		//getting names of players and creating player objects
		std::string p1Name, p2Name;
		std::cout << "Enter the name of player 1: ";
		std::cin >> p1Name;
		std::cout << "Enter the name of player 2: ";
		std::cin >> p2Name;

		player1 = new Player(p1Name);
		player2 = new Player(p2Name);



		deck = cf->getDeck();

		for (int i = 0; i < 5; i++) {
			player1->addCardToHand(deck.draw());
			player2->addCardToHand(deck.draw());
		}

		table = Table(*player1, *player2, deck, discardPile, tradeArea);
	}

		std::vector<Player*> players;
		//player 1 is at position 0 in vector and player 2 is at position 1 in vector
		players.push_back(player1);
		players.push_back(player2);


		while (deck.size() != 0) {
			std::string pause;
			std::cout << "Would you like to pause the game?(y/n): ";
			std::cin >> pause;
			if (pause == "y") {
				std::ofstream player1File("Player1.txt");
				std::ofstream player2File("Player2.txt");
				std::ofstream hand1File("Hand1.txt");
				std::ofstream hand2File("Hand2.txt");
				std::ofstream discardPileFile("DiscardPile.txt");
				std::ofstream tradeAreaFile("TradeArea.txt");
				std::ofstream deckFile("Deck.txt");
				std::ofstream tableFile("Table.txt");

				player1File << *player1;
				player2File << *player2;
				hand1File << (player1->getHand());
				hand2File << (player2->getHand());
				table.getDiscardPile().print(discardPileFile);
				tradeAreaFile << table.getTradeArea();
				deckFile << deck;
				tableFile << table;
				return 0;
			}
				else {
					for (int j = 0; j <= 1; j++) {

						//moi kin add sa
						if (deck.size() == 0) {
							break;
						}
						std::cout << "-----------------------------" << std::endl;
						std::cout << "\n" << players[j]->getName() << ", it's your turn!" << std::endl;
						std::cout << "Your hand is ";
						players[j]->getHand().displayHand();


						//allow player to buy a third chain
						if (players[j]->getNumCoins() >= 3) {
							std::string buyThird;
							std::cout << "Would you like to buy a third chain?(y/n): ";
							std::cin >> buyThird;
							if (buyThird == "y") {
								players[j]->buyThirdChain();
							}
						}

						if (j == 0) {
							players[0]->setActive(true);
							players[1]->setActive(false);
						}
						else {
							players[0]->setActive(false);
							players[1]->setActive(true);
						}


						table.displayTable();

						std::cout << "Your current fields are: " << std::endl;
						std::vector<Chain_Base*> playerChains = players[j]->getChain();
						//This loop displays the chains in the player's fields
						for (const auto& c : playerChains) {
							std::cout << *c << "\n";
						}
						/*This part of the program is concerned with Step 1*/

							while ((table.getTradeArea()).numCards() != 0) {
								std::string response;
								std::cout << "Would you like to add bean cards from trade area to your chains?(y/n): ";
								std::cin >> response;
								if (response == "y") {
									std::string cardToAdd;
									bool addAnotherChain = true;
									bool inTradeArea = false;
									
									//This loop checks if the card which the player wants to add is actually found in the trade area
									while (!inTradeArea) {
										std::cout << "Which card(s) would you like to add to your chain(s)? (Enter the name of the card e.g Red): ";
										std::cin >> cardToAdd;
										std::unordered_map<std::string, int> map = table.getTradeArea().getMap();
										for (const auto& pair : map) {
											if (pair.second != 0 && pair.first == cardToAdd) {
												inTradeArea = true;
											}
										}
										if (!inTradeArea) {
											std::cout << "This card is not in the trade area! Try again!" << std::endl;
										}
									}

									//This if statement would return false only if the player's fields are full
									if (!canAddCardFromTradeArea(*players[j], cardToAdd)) {
										std::cout << "Your fields are full and your fields do not match any of the cards in the trade area!" << std::endl;
										std::cout << "Your current fields are: " << std::endl;
										std::vector<Chain_Base*> playerChains = players[j]->getChain();
										//This loop displays the chains in the player's fields
										for (const auto& c : playerChains) {
											std::cout << *c << "\n";
										}
										bool valid = false;
										std::string fieldSell;

										//This loop checks if the name of the chain entered by the player is actually one of the chains in his fields
										while (!valid) {
											std::cout << "Which field would you like to sell?(Enter the name of the name eg Red): ";
											std::cin >> fieldSell;

											for (int i = 0; i < players[j]->getNumChains(); i++) {
												if (((playerChains.at(i))->getChainType()) == fieldSell) {
													valid = true;
													break;
												}
											}
											if (!valid) {
												std::cout << "This is bean is not in your field. Try again!" << std::endl;
											}
										}
										//Here we sell the corresponding chain
										players[j]->sellChain(fieldSell);
										std::cout << "Your coins after selling chain are " << players[j]->getNumCoins() << std::endl;
									}
									
									//This loop gets the number of cards to be added to the players fields from the chain selected
									std::unordered_map < std::string, int > map= table.getTradeArea().getMap();
									int n = 0;
									for (const auto& pair : map) {
										if (pair.first == cardToAdd) {
											n = pair.second;
											break;
										}
									}

									//This loop adds the cards chosen by the player to his/her fields and simultaneously removes them from the trade area
									for (int i = 0; i < n; i++) {
										players[j]->addCardToChain(table.getTradeArea().trade(cardToAdd), 1);
									}

									//This loop just prints out the players chains after having done any changes
									std::cout << "Your fields now contain the chains: " << std::endl;
									vector<Chain_Base*> chains = players[j]->getChain();
									for (const Chain_Base* cb : chains) {
										std::cout << "\n" << (*cb);
									}
									std::cout << std::endl;
								}
								else {
									//Since player does not want cards from trade area from previous step, we discard all cards from trading area
									int n = table.getTradeArea().numCards();
									for (int i = 0; i <n; i++) {
										table.getDiscardPile() += table.getTradeArea().removeCard();
									}
									//We break since player no longer wants cards from trade area
									break;
								}
							}
						

						/*This part of the program is concerned with Steps 2 and 3*/
						string repeat = "y";
						int timesPlayed = 0;
						while (repeat=="y" && timesPlayed < 2) {
							timesPlayed++;
							std::cout << "Your hand is ";
							players[j]->getHand().displayHand();

							Card* topmost = (players[j]->getHand()).play();
							std::cout << "Playing first card from your hand: " << topmost->getName() << std::endl;
							bool added = false;
							//if player has a field of the same type as his topmost card inhand, we add it to that chain

							for (const Chain_Base* cbPtr : players[j]->getChain()) {
								if (cbPtr->getChainType() == topmost->getName()) {
									players[j]->addCardToChain(topmost, 1);
									added = true;
									break;
								}
							}

							//if the player has an empty field, he plants his topmost bean from his hand there
							if (!added && (players[j]->getMaxNumChains() - players[j]->getNumChains() > 0)) {\

								players[j]->addCardToChain(topmost, 1);
								added = true;
							}

							//if the player cannot plant his topmost bean, he needs to sell a chain in his existing field
							if (!added) {
								std::cout << "Your fields are full and your topmost bean does not match any of your existing bean fields!" << std::endl;
								std::cout << "Your topmost bean is: " << topmost->getName() << std::endl;
								std::cout << "Choose a field to be sold from the following: ";
								std::vector<Chain_Base*> playerChains = players[j]->getChain();
								for (const auto cb : playerChains) {
									std::cout << (*cb);
									std::cout << "\n";
								}
								bool valid = false;
								std::string fieldSell;
								while (!valid) {
									std::cout << "Enter name of field to be sold: ";
									std::cin >> fieldSell;

									for (int i = 0; i < players[j]->getNumChains(); i++) {
										if (((playerChains.at(i))->getChainType()) == fieldSell) {
											valid = true;
											break;
										}
									}
									if (!valid) {
										std::cout << "This is bean is not in your field. Try again!"<<std::endl;
									}
								}
								players[j]->sellChain(fieldSell);
								players[j]->addCardToChain(topmost, 1);
								std::cout << "Your coins after selling chain are " << players[j]->getNumCoins() << std::endl;
							}

							std::cout << "After adding card from hand to chain(s), your chain(s) are: ";
							vector<Chain_Base*> chains = players[j]->getChain();
							for (const auto& cbPtr : chains) {
								std::cout << (*cbPtr);
							}
							std::cout << std::endl;

							//repeat these step if the player wants
							if (timesPlayed != 2) {
								players[j]->getHand().displayHand();
								std::cout << "\nWould you like to play another card from your hand?(y/n): ";
								std::cin >> repeat;
							}
						}

						/*This part of the program is concerned with Step 4*/
						std::cout << "\nYour hand is ";
						players[j]->getHand().displayHand();
						std::string deleteCard;
						std::cout << "Do you want to discard one of your cards from your hand?(y/n): ";
						std::cin >> deleteCard;
						if (deleteCard == "y") {
							std::cout << "Which card would you like to discard from the following?"<<std::endl;
							players[j]->getHand().displayHand();
							std::cout << "Please enter the position of the card that you want to discard(enter 0 for the first card, 1 for the second and so on): ";
							int pos;
							std::cin >> pos;
							while (pos<0 || pos >(players[j]->getHand()).getSize() - 1) {
								std::cout << "This is not a valid position in your hand! Try again." << std::endl;
								std::cout<< "Please enter the position of the card that you want to discard(enter 0 for the first card, 1 for the second and so on): ";
								std::cin >> pos;
							}
							Card* removed= ((players[j]->getHand()).removeCard(pos));
							(table.getDiscardPile()) += removed;
							
						}
						std::cout << "Your hand now is: ";
						players[j]->getHand().displayHand();


						/*This part of the program is concerned with Step 5*/
						for (int i = 0; i < 3; i++) {
							if (table.getDeck().size() != 0) {
								(table.getTradeArea()) += (table.getDeck()).draw();
							}
						}


						TradeArea tableTrade = table.getTradeArea();
						
						//Check if the discard pile is empty and also if top card matches
						

						while ((table.getDiscardPile().size() != 0) && tableTrade.legal(table.getDiscardPile().top())) {
							Card* card = table.getDiscardPile().pickUp();
							table.getTradeArea() += (card);
							
						}

						std::cout << "After drawing three cards from deck, and adding matching cards from discard pile, the trade area is: " << "\n";
						table.getTradeArea().updateMap();
						table.displayTable();

				
						while ((table.getTradeArea()).numCards() != 0) {
							std::string response;
							std::cout << "Would you like to add bean cards from trade area to your chains?(y/n): ";
							std::cin >> response;
							if (response == "y") {
								std::string cardToAdd;
								bool addAnotherChain = true;
								bool inTradeArea = false;

								//This loop checks if the card which the player wants to add is actually found in the trade area
								while (!inTradeArea) {
									std::cout << "Which card(s) would you like to add to your chain(s)? (Enter the name of the card e.g Red): ";
									std::cin >> cardToAdd;
									std::unordered_map<std::string, int> map = table.getTradeArea().getMap();
									for (const auto& pair : map) {
										if (pair.second != 0 && pair.first == cardToAdd) {
											inTradeArea = true;
										}
									}
									if (!inTradeArea) {
										std::cout << "This card is not in the trade area! Try again!" << std::endl;
									}
								}

								//This if statement would return false only if the player's fields are full
								if (!canAddCardFromTradeArea(*players[j], cardToAdd)) {
									std::cout << "Your fields are full and your fields do not match any of the cards in the trade area!" << std::endl;
									std::cout << "Your current fields are: " << std::endl;
									std::vector<Chain_Base*> playerChains = players[j]->getChain();
									//This loop displays the chains in the player's fields
									for (const auto& c : playerChains) {
										std::cout << *c << "\n";
									}
									bool valid = false;
									std::string fieldSell;

									//This loop checks if the name of the chain entered by the player is actually one of the chains in his fields
									while (!valid) {
										std::cout << "Which field would you like to sell?(Enter the name of the name eg Red): ";
										std::cin >> fieldSell;

										for (int i = 0; i < players[j]->getNumChains(); i++) {
											if (((playerChains.at(i))->getChainType()) == fieldSell) {
												valid = true;
												break;
											}
										}
										if (!valid) {
											std::cout << "This is bean is not in your field. Try again!" << std::endl;
										}
									}
									//Here we sell the corresponding chain
									players[j]->sellChain(fieldSell);
									std::cout << "Your coins after selling chain are " << players[j]->getNumCoins() << std::endl;
								}

								//This loop gets the number of cards to be added to the players fields from the chain selected
								std::unordered_map < std::string, int > map = table.getTradeArea().getMap();
								int n = 0;
								for (const auto& pair : map) {
									if (pair.first == cardToAdd) {
										n = pair.second;
										break;
									}
								}

								//This loop adds the cards chosen by the player to his/her fields and simultaneously removes them from the trade area
								for (int i = 0; i < n; i++) {
									players[j]->addCardToChain(table.getTradeArea().trade(cardToAdd), 1);
								}

								//This loop just prints out the players chains after having done any changes
								std::cout << "Your fields now contain the chains: " << std::endl;
								vector<Chain_Base*> chains = players[j]->getChain();
								for (const Chain_Base* cb : chains) {
									std::cout << "\n" << (*cb);
								}
								std::cout << std::endl;
							}
							else {
								//Break from loop if player does not want cards from trade area
								break;
							}
						}
						//draw 2 cards from deck and add to player's hand
						for (int i = 0; i < 2; i++) {
							if (table.getDeck().size() != 0) {
								players[j]->addCardToHand(deck.draw());
							}
						}
						std::cout << "After drawing two cards from deck, your hand is: " << std::endl;
						players[j]->getHand().displayHand();

					//}
					
				}
			}
		}

		//winning condition
		if (players[0]->getNumCoins() > players[1]->getNumCoins()) {
			std::cout << "The winner is: " << players[0]->getName() << "! Congratulations!";
		}
		else{
			if (players[1]->getNumCoins() > players[0]->getNumCoins()) {
				std::cout << "The winner is: " << players[1]->getName() << "! Congratulations!";
			}
			else {
				std::cout << "It's a draw!";
			}
		}
	


	return 0;
}
