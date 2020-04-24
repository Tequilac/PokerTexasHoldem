#pragma once

#include "card.h"
#include "random.h"

class Deck
{
private:
	Card cards[52];
	
public:
	Deck();
	
	Card getRandomCard();
	
	void refill();
	
};