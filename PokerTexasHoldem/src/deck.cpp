#include "deck.h"


Deck::Deck()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			cards[i * 13 + j].setColor(static_cast<Color>(i));
			cards[i * 13 + j].setRank(static_cast<Rank>(j + 2));
		}
	}
}
Card Deck::getRandomCard()
{
	int rand = (int)(Random::getRandom() * 52);
	while (cards[rand].getColor() == static_cast<Color>(-1))
	{
		rand = (int)(Random::getRandom() * 52);
	}
	Card card = cards[rand];
	cards[rand].setColor(static_cast<Color>(-1));
	return card;
}
void Deck::refill()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			cards[i * 13 + j].setColor(static_cast<Color>(i));
		}
	}
}