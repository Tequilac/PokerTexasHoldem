#include "button.h"


Button::Button(int width, int height, const int& x, const int& y, std::string txt, sf::Font& font)
{
	rectangle.setSize(sf::Vector2f(width, height));
	rectangle.setPosition(x, y);
	text.setFillColor(sf::Color::Black);
	text.setFont(font);
	text.setString(txt);
	text.setCharacterSize(20);
	text.setPosition(x + 1, y + 1);
}

void Button::draw(sf::RenderWindow& window)
{
	window.draw(rectangle);
	window.draw(text);
}

bool Button::checkForClick()
{
	if (sf::Mouse::getPosition().x > rectangle.getPosition().x && sf::Mouse::getPosition().x < (rectangle.getPosition().x + rectangle.getSize().x) &&
		sf::Mouse::getPosition().y > rectangle.getPosition().y && sf::Mouse::getPosition().y < (rectangle.getPosition().y + rectangle.getSize().y) &&
		sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return true;
	return false;
}

void Button::setText(const sf::String& newText)
{
	text.setString(newText);
}
