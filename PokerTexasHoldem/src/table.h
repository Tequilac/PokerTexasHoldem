#pragma once

#include <SFML/Graphics.hpp>
#include "deck.h"

class Table
{
private:
	Card cards[5];
	
	int size;
	
public:
	Table();
	
	int getSize() const;
	
	Card* getCards();
	
	void putFlop(Deck& deck);
	
	void putTurn(Deck& deck);
	
	void putRiver(Deck& deck);
	
	void loadTable(sf::Texture textures[5], sf::Sprite sprites[5], const int& windowWidth, const int& windowHeight);

	void makeEmpty();
};