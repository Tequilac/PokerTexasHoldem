#include "decisions.h"

void preflopMakeDecision(PlayerHand& player, int& highestBet, bool& raisedBet, int& raisedBy)
{
	if (player.getPassed() || player.getMoneyBid() == highestBet || player.getOutOfGame())
		return;
	if (player.getSum() < 13 || player.getMoney() < highestBet)
	{
		player.setPassed(true);
	}
	else
	{
		if (raisedBet)
		{
			player.setMoney(player.getMoney() - highestBet + player.getMoneyBid());
			player.setMoneyBid(highestBet);
		}
		else
		{
			highestBet = 3;
			raisedBet = true;
			player.setMoney(player.getMoney() - highestBet + player.getMoneyBid());
			player.setMoneyBid(highestBet);
		}
	}
}

int makeDecision(const Card* cards, const int& size)
{
	if (isRoyalFlush(cards, size))
	{
		return 20;
	}
	if (isStraightFlush(cards, size))
	{
		return 18;
	}
	if (isCloseToRoyalFlush(cards, size) || isQuads(cards, size))
	{
		return 16;
	}
	if (isCloseToStraightFlush(cards, size) || isFullHouse(cards, size))
	{
		return 14;
	}
	if (isCloseToQuads(cards, size) || isFlush(cards, size))
	{
		return 12;
	}
	if (isCloseToFullHouse(cards, size) || isStraight(cards, size))
	{
		return 10;
	}
	if (isCloseToFlush(cards, size) || isThree(cards, size))
	{
		return 8;
	}
	if (isCloseToStraight(cards, size) || isTwoPairs(cards, size))
	{
		return 6;
	}
	if (isCloseToThree(cards, size) || isPair(cards, size))
	{
		return 4;
	}
	if (isCloseToTwoPairs(cards, size) || isHighCard(cards, size))
	{
		return 2;
	}
	return 0;
}

void flopMakeDecision(Table& table, PlayerHand& player, int& highestBet, bool& raisedBet, int& raisedBy, bool& someoneBid)
{
	Card cards[5] = { table.getCards()[0], table.getCards()[1], table.getCards()[2], player.getCards()[0], player.getCards()[1] };
	quickSort(cards, 0, 4);
	int result = makeDecision(cards, 5);
	if (player.getPassed() || player.getMoneyBid() == highestBet)
		return;
	if (result < 3 || player.getMoney() < highestBet)
	{
		player.setPassed(true);
	}
	else if (result < 15)
	{
		if (raisedBet)
			player.setPassed(true);
		else if (!someoneBid && Random::getRandom() > 0.2)
			return;
		else
		{
			player.setMoney(player.getMoney() - highestBet + player.getMoneyBid());
			player.setMoneyBid(highestBet);
			someoneBid = true;
		}
	}
	else
	{
		if (raisedBet)
		{
			player.setMoney(player.getMoney() - highestBet + player.getMoneyBid());
			player.setMoneyBid(highestBet);
			someoneBid = true;
		}
		else
		{
			if (raisedBy == 0)
				raisedBy = (result - 5) * highestBet / 10 - highestBet;
			highestBet = highestBet + raisedBy;
			raisedBet = true;
			player.setMoney(player.getMoney() - highestBet + player.getMoneyBid());
			player.setMoneyBid(highestBet);
			someoneBid = true;
		}
	}
}

void turnMakeDecision(Table& table, PlayerHand& player, int& highestBet, bool& raisedBet, int& raisedBy, bool& someoneBid)
{
	int result;
	Card cards[6] = { table.getCards()[0], table.getCards()[1], table.getCards()[2], table.getCards()[3], player.getCards()[0], player.getCards()[1] };
	quickSort(cards, 0, 5);
	result = makeDecision(cards, 6);
	if (player.getPassed() || player.getMoneyBid() == highestBet)
		return;
	if (result < 3 || player.getMoney() < highestBet)
	{
		player.setPassed(true);
	}
	else if (result < 15)
	{
		if (raisedBet)
			player.setPassed(true);
		else if (!someoneBid && Random::getRandom() > 0.2)
			return;
		else
		{
			player.setMoney(player.getMoney() - highestBet + player.getMoneyBid());
			player.setMoneyBid(highestBet);
			someoneBid = true;
		}
	}
	else
	{
		if (raisedBet)
		{
			player.setMoney(player.getMoney() - highestBet + player.getMoneyBid());
			player.setMoneyBid(highestBet);
			someoneBid = true;
		}
		else
		{
			if (raisedBy == 0)
				raisedBy = (result - 5) * highestBet / 10 - highestBet;
			highestBet = highestBet + raisedBy;
			raisedBet = true;
			player.setMoney(player.getMoney() - highestBet + player.getMoneyBid());
			player.setMoneyBid(highestBet);
			someoneBid = true;
		}
	}
}

void riverMakeDecision(Table& table, PlayerHand& player, int& highestBet, bool& raisedBet, int& raisedBy, bool& someoneBid)
{
	int result;
	result = player.checkCombination(table);
	if (player.getPassed() || player.getMoneyBid() == highestBet)
		return;
	if (result < 3 || player.getMoney() < highestBet)
	{
		player.setPassed(true);
	}
	else if (result < 15)
	{
		if(highestBet - player.getMoneyBid() <= player.getMoney() + 10)
		{
			highestBet = highestBet + player.getMoney();
			player.setMoney(player.getMoney() - highestBet + player.getMoneyBid());
			player.setMoneyBid(highestBet);
			someoneBid = true;
		}
		if (raisedBet)
			player.setPassed(true);
		else if (!someoneBid && Random::getRandom() > 0.2)
			return;
		else
		{
			player.setMoney(player.getMoney() - highestBet + player.getMoneyBid());
			player.setMoneyBid(highestBet);
			someoneBid = true;
		}
	}
	else
	{
		if (highestBet - player.getMoneyBid() <= player.getMoney() + 10)
		{
			highestBet = highestBet + player.getMoney();
			player.setMoney(player.getMoney() - highestBet + player.getMoneyBid());
			player.setMoneyBid(highestBet);
			someoneBid = true;
		}
		else if (raisedBet)
		{
			player.setMoney(player.getMoney() - highestBet + player.getMoneyBid());
			player.setMoneyBid(highestBet);
			someoneBid = true;
		}
		else
		{
			if (raisedBy == 0)
				raisedBy = (result - 5) * highestBet / 10 - highestBet;
			highestBet = highestBet + raisedBy;
			raisedBet = true;
			player.setMoney(player.getMoney() - highestBet + player.getMoneyBid());
			player.setMoneyBid(highestBet);
			someoneBid = true;
		}
	}
}