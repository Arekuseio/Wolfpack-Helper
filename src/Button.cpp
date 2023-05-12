#include "Button.h"


Button::Button(std::string btnText, sf::Vector2f buttonSize, int charSize, sf::Color bgColor, sf::Color textColor) {
	button.setSize(buttonSize);
	button.setFillColor(bgColor);

	// Get these for later use:
	btnWidth = buttonSize.x;
	btnHeight = buttonSize.y;

	text.setString(btnText);
	text.setCharacterSize(charSize);
	text.setColor(textColor);
}

void Button::setClickEvent(std::function<void()> func) {
	onClickedEvent = func;
}

void Button::setMouseOverEvent(std::function<void()> func) {
	onMouseOverEvent = func;
}

void Button::setMouseNotOverEvent(std::function<void()> func) {
	onMouseNotOverEvent = func;
}

void Button::onClicked() {
	if (onClickedEvent != nullptr)
		onClickedEvent();
}

void Button::onMouseOver() {
	if (onMouseOverEvent != nullptr)
		onMouseOverEvent();
}

void Button::onMouseNotOver() {
	if (onMouseNotOverEvent != nullptr)
		onMouseNotOverEvent();
}

void Button::setFont(sf::Font& fonts) {
	text.setFont(fonts);
}

void Button::setBackColor(sf::Color color) {
	button.setFillColor(color);
}

void Button::setTextColor(sf::Color color) {
	text.setColor(color);
}

void Button::setPosition(sf::Vector2f point) {
	button.setPosition(point);

	// Center text on button:
	float xPos = (point.x + btnWidth / 2) - (text.getLocalBounds().width / 2);
	float yPos = (point.y + btnHeight / 2.2) - (text.getLocalBounds().height / 2);
	text.setPosition(xPos, yPos);
}

void Button::drawTo(sf::RenderWindow& window) {
	window.draw(button);
	window.draw(text);
}

// Check if the mouse is within the bounds of the button:
bool Button::isMouseOver(sf::RenderWindow& window) {
	int mouseX = sf::Mouse::getPosition(window).x;
	int mouseY = sf::Mouse::getPosition(window).y;

	int btnPosX = button.getPosition().x;
	int btnPosY = button.getPosition().y;

	int btnxPosWidth = button.getPosition().x + btnWidth;
	int btnyPosHeight = button.getPosition().y + btnHeight;

	if (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY) {
		return true;
	}
	return false;
}