#pragma once

#include "deck.h"
#include "card.h"

bool isRoyalFlush(const Card* cards, const int& size);


bool isStraightFlush(const Card* cards, const int& size);


bool isQuads(const Card* cards, const int& size);


bool isFullHouse(const Card* cards, const int& size);


bool isFlush(const Card* cards, const int& size);


bool isStraight(const Card* cards, const int& size);


bool isThree(const Card* cards, const int& size);


bool isTwoPairs(const Card* cards, const int& size);


bool isPair(const Card* cards, const int& size);


bool isHighCard(const Card* cards, const int& size);


bool isCloseToRoyalFlush(const Card* cards, const int& size);


bool isCloseToStraightFlush(const Card* cards, const int& size);


bool isCloseToQuads(const Card* cards, const int& size);


bool isCloseToFullHouse(const Card* cards, const int& size);


bool isCloseToFlush(const Card* cards, const int& size);


bool isCloseToStraight(const Card* cards, const int& size);


bool isCloseToThree(const Card* cards, const int& size);


bool isCloseToTwoPairs(const Card* cards, const int& size);