#include "player.h"

PlayerHand::PlayerHand()
{
	money = 200;
	moneyBid = 0;
	cards[0].setRank(static_cast<Rank>(14));
	cards[0].setColor(static_cast<Color>(-1));
	cards[1].setRank(static_cast<Rank>(14));
	cards[1].setColor(static_cast<Color>(-1));
}

Card* PlayerHand::getCards()
{
	return cards;
}

int PlayerHand::getMoney() const
{
	return money;
}

int PlayerHand::getMoneyBid() const
{
	return moneyBid;
}

bool PlayerHand::getPassed() const
{
	return passed;
}

bool PlayerHand::getOutOfGame() const
{
	return outOfGame;
}


void PlayerHand::setMoney(const int& money)
{
	this->money = money;
}

void PlayerHand::setMoneyBid(const int& money)
{
	this->moneyBid = money;
}

void PlayerHand::setFirstCard(const Card& card)
{
	this->cards[0] = card;
}

void PlayerHand::setPassed(const bool& passed)
{
	this->passed = passed;
}

void PlayerHand::setSecondCard(const Card& card)
{
	this->cards[1] = card;
}

void PlayerHand::setOutOfGame(const bool& out)
{
	this->outOfGame = out;
}


int PlayerHand::getSum()
{
	return getCards()[0].getRank() + getCards()[1].getRank();
}

int PlayerHand::checkCombination(Table table)
{
	Card playerCards[7] = {};
	playerCards[0] = this->getCards()[0];
	playerCards[1] = this->getCards()[1];
	for (int i = 0; i < table.getSize(); i++)
	{
		playerCards[i + 2] = table.getCards()[i];
	}
	quickSort(playerCards, 0, 6);
	int size = 2 + table.getSize();
	if (isRoyalFlush(playerCards, size))
	{
		return 20;
	}
	if (isStraightFlush(playerCards, size))
	{
		return 18;
	}
	if (isQuads(playerCards, size))
	{
		return 16;
	}
	if (isFullHouse(playerCards, size))
	{
		return 14;
	}
	if (isFlush(playerCards, size))
	{
		return 12;
	}
	if (isStraight(playerCards, size))
	{
		return 10;
	}
	if (isThree(playerCards, size))
	{
		return 8;
	}
	if (isTwoPairs(playerCards, size))
	{
		return 6;
	}
	if (isPair(playerCards, size))
	{
		return 4;
	}
	if (isHighCard(playerCards, size))
	{
		return 2;
	}
	return 0;
}