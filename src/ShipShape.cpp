#include "ShipShape.h"
#define pi 3.14f

size_t ShipShape::getPointCount() const {
	return this->pointsNum;
}

sf::Vector2f ShipShape::getPoint(std::size_t index) const { // TODO: Сделать shape корабля прямоугольным
	float angle = index * pi * 2.f / getPointCount() ;
	
	float x = size.x * std::cos(angle) / 2.f;
	float y = size.y * std::sin(angle) / 2.f;

	//sf::RectangleShape shape(sf::Vector2f(size.x, size.y));
	//shape.setPosition(this->getPosition());
 	//sf::Vector2f point = shape.getPoint(index);

	return sf::Vector2f(x + this->getPosition().x, y + this->getPosition().y);
}