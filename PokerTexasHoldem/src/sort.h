#pragma once

#include "card.h"



bool cardsCompare(const Card& card1, const Card& card2);

int partition(Card arr[], int low, int high);

void quickSort(Card arr[], int low, int high);