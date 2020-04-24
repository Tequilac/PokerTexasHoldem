#pragma once

#include "player.h"


void blinds(PlayerHand players[6], const int& dealer, int& highestBet, bool& someoneBid);

void giveCards(Deck& deck, PlayerHand players[6]);

void doAction(PlayerHand& player, const int& action, int& highestBet, bool& raisedBet, int& raisedBy, bool& someoneBid);

void loadSprites(sf::Texture textures[12], sf::Sprite sprites[12], PlayerHand players[6], const bool& shown, const int& windowWidth, const int& windowHeight);

bool allPassedOrEqual(PlayerHand players[6], int& highestBet);

void transferMoneyToTable(PlayerHand players[6], int& moneyOnTable);

void transferMoneyToWinners(PlayerHand players[6], std::vector<int>& winners, int& moneyOnTable);

std::vector<int> determineIfSomeoneWon(PlayerHand players[6], Table& table);