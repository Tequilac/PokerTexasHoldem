#pragma once

#include <SFML/Graphics.hpp>

class Button
{
private:
	sf::RectangleShape rectangle;
	
	sf::Text text;
	
public:
	Button(int width, int height, const int& x, const int& y, std::string txt, sf::Font& font);
	
	void draw(sf::RenderWindow& window);
	
	bool checkForClick();

	void setText(const sf::String& newText);
};