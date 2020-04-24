#pragma once

#include <iostream>
#include <string>

enum Color
{
	None = -1,
	Clubs = 0,
	Diamonds = 1,
	Hearts = 2,
	Spades = 3
};

inline
std::ostream& operator<<(std::ostream& str, const Color& data);

enum Rank
{
	Two = 2,
	Three = 3,
	Four = 4,
	Five = 5,
	Six = 6,
	Seven = 7,
	Eight = 8,
	Nine = 9,
	Ten = 10,
	Jack = 11,
	Queen = 12,
	King = 13,
	Ace = 14
};

inline
std::ostream& operator<<(std::ostream& str, Rank const& data);

class Card
{
private:
	Color color;
	
	Rank rank;
	
public:
	Color getColor() const;
	
	Rank getRank() const;
	
	void setColor(const Color& color);
	
	void setRank(const Rank& rank);
	
	std::string getImage() const;
	
};

inline
std::ostream& operator<<(std::ostream& str, Card& data);