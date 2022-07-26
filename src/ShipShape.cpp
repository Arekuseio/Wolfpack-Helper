#include "ShipShape.h"
#define pi 3.14f

size_t ShipShape::getPointCount() const {
	return this->pointsNum;
}

sf::Vector2f ShipShape::getPoint(std::size_t index) const {
	float angle = index * pi * 2.f / getPointCount() ;
	
	float x = size.x * std::cos(angle);
	float y = size.y * std::sin(angle);

	sf::Vector2f pos = this->getPosition();

	return sf::Vector2f(x + this->getPosition().x, y + this->getPosition().y);
}