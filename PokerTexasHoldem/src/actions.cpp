#include "actions.h"


void blinds(PlayerHand players[6], const int& dealer, int& highestBet, bool& someoneBid)
{
	players[(dealer + 1) % 6].setMoney(players[(dealer + 1) % 6].getMoney() - 1);
	players[(dealer + 1) % 6].setMoneyBid(1);
	highestBet = 2;
	players[(dealer + 2) % 6].setMoney(players[(dealer + 2) % 6].getMoney() - 2);
	players[(dealer + 2) % 6].setMoneyBid(2);
	someoneBid = true;
}

void giveCards(Deck& deck, PlayerHand players[6])
{
	for (int i = 0; i < 6; i++)
	{
		if (!players[i].getOutOfGame())
		{
			players[i].setFirstCard(deck.getRandomCard());
			players[i].setSecondCard(deck.getRandomCard());
		}
	}
}

void doAction(PlayerHand& player, const int& action, int& highestBet, bool& raisedBet, int& raisedBy, bool& someoneBid)
{
	if (action == 0)
	{
		player.setPassed(true);
	}
	else if (action == 1)
	{
		player.setMoney(player.getMoney() - highestBet + player.getMoneyBid());
		player.setMoneyBid(highestBet);
		someoneBid = true;
	}
	else if (action == 2)
	{
		return;
	}
	else
	{
		if (action - highestBet > raisedBy)
			raisedBy = action - highestBet;
		highestBet = action;
		raisedBet = true;
		player.setMoney(player.getMoney() - highestBet + player.getMoneyBid());
		player.setMoneyBid(highestBet);
		someoneBid = true;
	}

}



void loadSprites(sf::Texture textures[12], sf::Sprite sprites[12], PlayerHand players[6], const bool& shown, const int& windowWidth, const int& windowHeight)
{
	if (shown)
	{
		for (int i = 0; i < 6; i++)
			if (!players[i].getOutOfGame())
				for (int j = 0; j < 2; j++)
				{
					textures[i * 2 + j].loadFromFile(players[i].getCards()[j].getImage());
					textures[i * 2 + j].setSmooth(true);
				}
	}
	else
	{
		for (int i = 0; i < 6; i++)
		{
			if (i == 4)
			{
				if (!players[i].getOutOfGame())
					for (int j = 0; j < 2; j++)
					{
						textures[i * 2 + j].loadFromFile(players[i].getCards()[j].getImage());
						textures[i * 2 + j].setSmooth(true);
					}
			}
			else
			{
				if (players[i].getPassed())
				{
					if (!players[i].getOutOfGame())
						for (int j = 0; j < 2; j++)
						{
							textures[i * 2 + j].loadFromFile("res/gray_back.png");
							textures[i * 2 + j].setSmooth(true);
						}
				}
				else
				{
					if (!players[i].getOutOfGame())
						for (int j = 0; j < 2; j++)
						{
							textures[i * 2 + j].loadFromFile("res/green_back.png");
							textures[i * 2 + j].setSmooth(true);
						}
				}
			}
		}
	}


	float positions[24] = { 10, 190, 120, 190,
							850, 10, 960, 10,
							1690, 190, 1800, 190,
							1690, 730, 1800, 730,
							850, 910, 960, 910,
							10, 730, 120, 730 };
	for (int i = 0; i < 12; i++)
	{
		positions[i * 2] *= (float)windowWidth / 1920;
		positions[i * 2 + 1] *= (float)windowHeight / 1080;
	}
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 2; j++)
		{
			sprites[i * 2 + j] = sf::Sprite(textures[i * 2 + j]);
			sprites[i * 2 + j].setScale(0.15f, 0.15f);
			sprites[i * 2 + j].setPosition(positions[(i * 2 + j) * 2], positions[(i * 2 + j) * 2 + 1]);
		}
}

bool allPassedOrEqual(PlayerHand players[6], int& highestBet)
{
	bool passedOrEqual = true;
	for (int i = 0; i < 6; i++)
	{
		if (players[i].getMoneyBid() != highestBet && players[i].getPassed() != true)
			passedOrEqual = false;
	}
	return passedOrEqual;
}

void transferMoneyToTable(PlayerHand players[6], int& moneyOnTable)
{
	for (int i = 0; i < 6; i++)
	{
		moneyOnTable += players[i].getMoneyBid();
		players[i].setMoneyBid(0);
	}
}

void transferMoneyToWinners(PlayerHand players[6], std::vector<int>& winners, int& moneyOnTable)
{
	int prize = moneyOnTable / winners.size();
	for (int i = 0; i < winners.size(); i++)
	{
		players[winners[i]].setMoney(players[winners[i]].getMoney() + prize);
		moneyOnTable -= prize;
	}
}

std::vector<int> determineIfSomeoneWon(PlayerHand players[6], Table& table)
{
	std::vector<int> winners;
	int notPassedNumbers[6];
	int notPassed = 0;
	for (int i = 0; i < 6; i++)
	{
		if (!players[i].getPassed() && !players[i].getOutOfGame())
		{
			notPassedNumbers[notPassed] = i;
			notPassed++;
		}
	}
	if (notPassed == 1)
	{
		winners.push_back(notPassedNumbers[0]);
		return winners;
	}
	if (table.getSize() != 5)
	{
		winners.push_back(-1);
		return winners;
	}
	int highestNumbers[6];
	for (int i = 0; i < notPassed; i++)
	{
		highestNumbers[i] = players[notPassedNumbers[i]].checkCombination(table);
	}
	int maxVal = highestNumbers[0];
	winners.push_back(notPassedNumbers[0]);
	for (int i = 1; i < notPassed; i++)
	{
		if (highestNumbers[i] > maxVal)
		{
			maxVal = highestNumbers[i];
			winners.clear();
			winners.push_back(notPassedNumbers[i]);
		}
		else if (highestNumbers[i] == maxVal)
		{
			winners.push_back(notPassedNumbers[i]);
		}
	}
	return winners;
}