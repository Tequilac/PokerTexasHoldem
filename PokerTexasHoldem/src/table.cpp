#include "table.h"

Table::Table()
{
	size = 0;
}

int Table::getSize() const
{
	return size;
}

Card* Table::getCards()
{
	return cards;
}

void Table::putFlop(Deck& deck)
{
	cards[0] = deck.getRandomCard();
	cards[1] = deck.getRandomCard();
	cards[2] = deck.getRandomCard();
	size = 3;
}

void Table::putTurn(Deck& deck)
{
	cards[3] = deck.getRandomCard();
	size = 4;
}

void Table::putRiver(Deck& deck)
{
	cards[4] = deck.getRandomCard();
	size = 5;
}

void Table::loadTable(sf::Texture textures[5], sf::Sprite sprites[5], const int& windowWidth, const int& windowHeight)
{
	for (int i = 0; i < size; i++)
	{
		textures[i].loadFromFile(cards[i].getImage());
		textures[i].setSmooth(true);
	}


	float positions[10] = {	650, 500,
							770, 500,
							890, 500,
							1010, 500,
							1130, 500 };
	for (int i = 0; i < 12; i++)
	{
		positions[i * 2] *= (float)windowWidth / 1920;
		positions[i * 2 + 1] *= (float)windowHeight / 1080;
	}
	for (int i = 0; i < size; i++)
	{
		sprites[i] = sf::Sprite(textures[i]);
		sprites[i].setScale(0.15f, 0.15f);
		sprites[i].setPosition(positions[i * 2], positions[i * 2 + 1]);
	}
}

void Table::makeEmpty()
{
	size = 0;
}
