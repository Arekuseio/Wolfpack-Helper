#pragma once

#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>

class Button {
public:
	Button(std::string btnText, sf::Vector2f buttonSize, int charSize, sf::Color bgColor, sf::Color textColor);

	// Pass font by reference:
	void setFont(sf::Font& fonts);
	void setBackColor(sf::Color color);
	void setTextColor(sf::Color color);
	void setPosition(sf::Vector2f point);
	void setClickEvent(std::function<void()> func);
	void setMouseOverEvent(std::function<void()> func);
	void setMouseNotOverEvent(std::function<void()> func);

	void drawTo(sf::RenderWindow& window);

	// Check if the mouse is within the bounds of the button:
	bool isMouseOver(sf::RenderWindow& window);

	void onClicked();
	void onMouseOver();
	void onMouseNotOver();

private:
	sf::RectangleShape button;
	sf::Text text;

	std::function<void()> onClickedEvent;
	std::function<void()> onMouseOverEvent;
	std::function<void()> onMouseNotOverEvent;

	int btnWidth;
	int btnHeight;
};
