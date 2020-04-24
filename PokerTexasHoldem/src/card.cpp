#include "card.h"



inline
std::ostream& operator<<(std::ostream& str, const Color& data)
{
	switch (data)
	{
	case -1: str << "None";
		break;
	case 0: str << "Clubs";
		break;
	case 1: str << "Diamonds";
		break;
	case 2: str << "Hearts";
		break;
	case 3: str << "Spades";
		break;
	}
	return str;
}


inline
std::ostream& operator<<(std::ostream& str, Rank const& data)
{
	switch (data)
	{
	case 2: str << "Two";
		break;
	case 3: str << "Three";
		break;
	case 4: str << "Four";
		break;
	case 5: str << "Five";
		break;
	case 6: str << "Six";
		break;
	case 7: str << "Seven";
		break;
	case 8: str << "Eight";
		break;
	case 9: str << "Nine";
		break;
	case 10: str << "Ten";
		break;
	case 11: str << "Jack";
		break;
	case 12: str << "Queen";
		break;
	case 13: str << "King";
		break;
	case 14: str << "Ace";
		break;
	}
	return str;
}


Color Card::getColor() const
{
	return color;
}
Rank Card::getRank() const
{
	return rank;
}
void Card::setColor(const Color& color)
{
	this->color = color;
}
void Card::setRank(const Rank& rank)
{
	this->rank = rank;
}
std::string Card::getImage() const
{
	std::string file = "res/";
	if (this->getRank() < 11)
		file += std::to_string(this->getRank());
	else
	{
		switch (this->getRank())
		{
		case 11: file += "J";
			break;
		case 12: file += "Q";
			break;
		case 13: file += "K";
			break;
		case 14: file += "A";
			break;
		}
	}
	switch (this->getColor())
	{
	case 0: file += "C";
		break;
	case 1: file += "D";
		break;
	case 2: file += "H";
		break;
	case 3: file += "S";
		break;
	}
	file += ".png";
	return file;
}


inline
std::ostream& operator<<(std::ostream& str, Card& data)
{
	str << data.getRank() << " of " << data.getColor();
	return str;
}