#pragma once

#include "combinations.h"
#include "table.h"
#include "deck.h"
#include "sort.h"

class PlayerHand
{
private:
	Card cards[2];
	
	int money;
	
	int moneyBid;
	
	bool passed = false;
	
	bool waited = false;

	bool outOfGame = false;
	
public:
	PlayerHand();
	
	Card* getCards();
	
	int getMoney() const;
	
	int getMoneyBid() const;
	
	bool getPassed() const;

	bool getOutOfGame() const;
	
	void setMoney(const int& money);
	
	void setMoneyBid(const int& money);
	
	void setFirstCard(const Card& card);
	
	void setPassed(const bool& passed);
	
	void setSecondCard(const Card& card);

	void setOutOfGame(const bool& out);
	
	int getSum();
	
	int checkCombination(Table table);
	
};