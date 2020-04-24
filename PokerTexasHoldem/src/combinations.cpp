#include "combinations.h"


bool isRoyalFlush(const Card* cards, const int& size)
{
	if (!isFlush(cards, size))
		return false;
	Color color = cards[0].getColor();
	if (size == 5)
	{
		for (int i = 0; i < 5; i++)
		{
			if (cards[i].getRank() != 10 + i || cards[i].getColor() != color)
				return false;
		}
		return true;
	}
	if (size == 6)
	{
		color = cards[0].getColor();
		for (int i = 0; i < 5; i++)
		{
			if (cards[i].getRank() != 10 + i || cards[i].getColor() != color)
				break;
			if (i == 4)
				return true;
		}
		color = cards[1].getColor();
		for (int i = 1; i < 6; i++)
		{
			if (cards[i].getRank() != 10 + i || cards[i].getColor() != color)
				break;
			if (i == 4)
				return true;
		}
		return false;
	}
	if (size == 7)
	{
		color = cards[0].getColor();
		for (int i = 0; i < 5; i++)
		{
			if (cards[i].getRank() != 10 + i || cards[i].getColor() != color)
				break;
			if (i == 4)
				return true;
		}
		color = cards[1].getColor();
		for (int i = 1; i < 6; i++)
		{
			if (cards[i].getRank() != 10 + i || cards[i].getColor() != color)
				break;
			if (i == 5)
				return true;
		}
		color = cards[2].getColor();
		for (int i = 2; i < 7; i++)
		{
			if (cards[i].getRank() != 10 + i || cards[i].getColor() != color)
				break;
			if (i == 6)
				return true;
		}
		return false;
	}
	return false;
}


bool isStraightFlush(const Card* cards, const int& size)
{
	if (!isFlush(cards, size))
		return false;
	Rank lowest;
	Color color = cards[0].getColor();
	if (size == 5)
	{
		lowest = cards[0].getRank();
		for (int i = 1; i < 5; i++)
		{
			if (cards[i].getRank() != lowest + i || cards[i].getColor() != color)
				return false;
		}
		return true;
	}
	if (size == 6)
	{
		color = cards[0].getColor();
		lowest = cards[0].getRank();
		for (int i = 1; i < 5; i++)
		{
			if (cards[i].getRank() != lowest + i || cards[i].getColor() != color)
				break;
			if (i == 4)
				return true;
		}
		color = cards[1].getColor();
		lowest = cards[1].getRank();
		for (int i = 2; i < 6; i++)
		{
			if (cards[i].getRank() != lowest + i || cards[i].getColor() != color)
				break;
			if (i == 4)
				return true;
		}
		return false;
	}
	if (size == 7)
	{
		color = cards[0].getColor();
		lowest = cards[0].getRank();
		for (int i = 1; i < 5; i++)
		{
			if (cards[i].getRank() != lowest + i || cards[i].getColor() != color)
				break;
			if (i == 4)
				return true;
		}
		color = cards[1].getColor();
		lowest = cards[1].getRank();
		for (int i = 2; i < 6; i++)
		{
			if (cards[i].getRank() != lowest + i || cards[i].getColor() != color)
				break;
			if (i == 5)
				return true;
		}
		color = cards[2].getColor();
		lowest = cards[2].getRank();
		for (int i = 3; i < 7; i++)
		{
			if (cards[i].getRank() != lowest + i || cards[i].getColor() != color)
				break;
			if (i == 6)
				return true;
		}
		return false;
	}
	return false;
}


bool isQuads(const Card* cards, const int& size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			for (int k = 0; k < size; k++)
			{
				for (int l = 0; l < size; l++)
				{
					if (i != j && i != k && i != l && j != k && j != l && k != l 
						&& cards[i].getRank() == cards[j].getRank() && cards[i].getRank() == cards[k].getRank() && cards[i].getRank() == cards[l].getRank())
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}


bool isFullHouse(const Card* cards, const int& size)
{
	bool isThree = false;
	Rank rank;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			for (int k = 0; k < size; k++)
			{
				if (i != j && i != k && j != k && cards[i].getRank() == cards[j].getRank() && cards[i].getRank() == cards[k].getRank())
				{
					rank = cards[i].getRank();
					isThree = true;
				}
			}
		}
	}
	if (!isThree)
		return false;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (i != j && cards[i].getRank() == cards[j].getRank() && cards[i].getRank() != rank)
				return true;
		}
	}
	return false;
}


bool isFlush(const Card* cards, const int& size)
{
	int colors[4] = { 0, 0, 0, 0 };
	for (int i = 0; i < size; i++)
	{
		colors[cards[i].getColor()]++;
	}
	for (int i = 0; i < 4; i++)
	{
		if (colors[i] > 4)
			return true;
	}
	return false;
}


bool isStraight(const Card* cards, const int& size)
{
	bool isFive;
	bool fits;
	for (int i = 2; i < 10; i++)
	{
		isFive = true;
		for (int j = 0; j < 5; j++)
		{
			fits = false;
			for (int k = 0; k < size; k++)
			{
				if (cards[k].getRank() == i + j)
				{
					fits = true;
					break;
				}
			}
			if (!fits)
			{
				isFive = false;
				break;
			}
		}
		if (isFive)
			return true;
	}
	return false;
}


bool isThree(const Card* cards, const int& size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			for (int k = 0; k < size; k++)
			{
				if (i != j && i != k && j != k && cards[i].getRank() == cards[j].getRank() && cards[i].getRank() == cards[k].getRank())
					return true;
			}
		}
	}
	return false;
}


bool isTwoPairs(const Card* cards, const int& size)
{
	bool onePair = false;
	Rank pairRank;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (i != j && cards[i].getRank() == cards[j].getRank())
			{
				if (!onePair)
				{
					onePair = true;
					pairRank = cards[i].getRank();
				}
				else
				{
					if (cards[i].getRank() != pairRank)
						return true;
				}
			}
		}
	}
	return false;
}


bool isPair(const Card* cards, const int& size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (i != j && cards[i].getRank() == cards[j].getRank())
				return true;
		}
	}
	return false;
}


bool isHighCard(const Card* cards, const int& size)
{
	for (int i = 0; i < size; i++)
	{
		if (cards[i].getRank() > size + 5)
			return true;
	}
	return false;
}


bool isCloseToRoyalFlush(const Card* cards, const int& size)
{
	if (!isFlush(cards, size))
		return false;
	Color color = cards[0].getColor();
	if (size == 5)
	{
		for (int i = 0; i < 5; i++)
		{
			for(int j = 0; j < 5; j++)
			{
				if (i == j)
					i++;
				if (cards[i].getRank() != 10 + i || cards[i].getColor() != color)
					return false;
			}
		}
		return true;
	}
	if (size == 6)
	{
		color = cards[0].getColor();
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (i == j)
					i++;
				if (cards[i].getRank() != 10 + i || cards[i].getColor() != color)
					break;
			}
			if (i == 4)
				return true;
		}
		color = cards[1].getColor();
		for (int i = 1; i < 6; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (i == j)
					i++;
				if (cards[i].getRank() != 10 + i || cards[i].getColor() != color)
					break;
			}
			if (i == 5)
				return true;
		}
		return false;
	}
	if (size == 7)
	{
		color = cards[0].getColor();
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (i == j)
					i++;
				if (cards[i].getRank() != 10 + i || cards[i].getColor() != color)
					break;
			}
			if (i == 4)
				return true;
		}
		color = cards[1].getColor();
		for (int i = 1; i < 6; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (i == j)
					i++;
				if (cards[i].getRank() != 10 + i || cards[i].getColor() != color)
					break;
			}
			if (i == 5)
				return true;
		}
		color = cards[2].getColor();
		for (int i = 2; i < 7; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (i == j)
					i++;
				if (cards[i].getRank() != 10 + i || cards[i].getColor() != color)
					break;
			}
			if (i == 6)
				return true;
		}
		return false;
	}
	return false;
}


bool isCloseToStraightFlush(const Card* cards, const int& size)
{
	if (!isFlush(cards, size))
		return false;
	Rank lowest;
	Color color = cards[0].getColor();
	if (size == 5)
	{
		lowest = cards[0].getRank();
		for (int i = 1; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (i == j)
					i++;
				if (cards[i].getRank() != lowest + i || cards[i].getColor() != color)
					return false;
			}
		}
		return true;
	}
	if (size == 6)
	{
		lowest = cards[0].getRank();
		for (int i = 1; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (i == j)
					i++;
				if (cards[i].getRank() != lowest + i || cards[i].getColor() != color)
					break;
			}
			if (i == 4)
				return true;
		}
		color = cards[1].getColor();
		lowest = cards[1].getRank();
		for (int i = 2; i < 6; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (i == j)
					i++;
				if (cards[i].getRank() != lowest + i || cards[i].getColor() != color)
					break;
			}
			if (i == 5)
				return true;
		}
		return false;
	}
	if (size == 7)
	{
		lowest = cards[0].getRank();
		for (int i = 1; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (i == j)
					i++;
				if (cards[i].getRank() != lowest + i || cards[i].getColor() != color)
					break;
			}
			if (i == 4)
				return true;
		}
		color = cards[1].getColor();
		lowest = cards[1].getRank();
		for (int i = 2; i < 6; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (i == j)
					i++;
				if (cards[i].getRank() != lowest + i || cards[i].getColor() != color)
					break;
			}
			if (i == 5)
				return true;
		}
		color = cards[2].getColor();
		lowest = cards[2].getRank();
		for (int i = 3; i < 7; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (i == j)
					i++;
				if (cards[i].getRank() != lowest + i || cards[i].getColor() != color)
					break;
			}
			if (i == 6)
				return true;
		}
		return false;
	}
	return false;
}


bool isCloseToQuads(const Card* cards, const int& size)
{
	return isThree(cards, size);
}


bool isCloseToFullHouse(const Card* cards, const int& size)
{
	return isTwoPairs(cards, size) || isThree(cards, size);
}


bool isCloseToFlush(const Card* cards, const int& size)
{
	int colors[4] = { 0, 0, 0, 0 };
	for (int i = 0; i < size; i++)
	{
		colors[cards[i].getColor()]++;
	}
	for (int i = 0; i < 4; i++)
	{
		if (colors[i] > 3)
			return true;
	}
	return false;
}


bool isCloseToStraight(const Card* cards, const int& size)
{
	bool isFive;
	int fit;
	for (int i = 2; i < 10; i++)
	{
		isFive = true;
		for (int j = 0; j < 5; j++)
		{
			fit = 0;
			for (int k = 0; k < size; k++)
			{
				if (cards[k].getRank() == i + j)
				{
					fit++;
					break;
				}
			}
			if (fit < 4)
			{
				isFive = false;
				break;
			}
		}
		if (isFive)
			return true;
	}
	return false;
}


bool isCloseToThree(const Card* cards, const int& size)
{
	return isPair(cards, size);
}


bool isCloseToTwoPairs(const Card* cards, const int& size)
{
	return isPair(cards, size);
}