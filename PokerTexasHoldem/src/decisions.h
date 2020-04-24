#pragma once

#include "sort.h"
#include "player.h"
#include "combinations.h"


void preflopMakeDecision(PlayerHand& player, int& highestBet, bool& raisedBet, int& raisedBy);

int makeDecision(const Card* cards, const int& size);

void flopMakeDecision(Table& table, PlayerHand& player, int& highestBet, bool& raisedBet, int& raisedBy, bool& someoneBid);

void turnMakeDecision(Table& table, PlayerHand& player, int& highestBet, bool& raisedBet, int& raisedBy, bool& someoneBid);

void riverMakeDecision(Table& table, PlayerHand& player, int& highestBet, bool& raisedBet, int& raisedBy, bool& someoneBid);