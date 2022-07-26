#pragma once
#include <SFML/Graphics.hpp>

class ShipShape : public sf::Shape {
public:
	ShipShape(const sf::Texture& shipTexture, const sf::Vector2i& size, const size_t pointsNum) {
		this->setTexture(&shipTexture);
		this->size = size;
		this->pointsNum = pointsNum;
		update();
	}

	ShipShape() { }

	void setPointsNum(const size_t new_num) {
		this->pointsNum = new_num;
		update();
	}

	size_t getPointsNum() const {
		return this->pointsNum;
	}

	void setSize(const sf::Vector2i& new_size) {
		this->size = new_size;
		update();
	}

	const sf::Vector2i& getSize() const {
		return this->size;
	}
	
	virtual size_t getPointCount() const;

	virtual sf::Vector2f getPoint(std::size_t index) const;
private:

	// Biggest and smallest radiuses of the ellipse shape of ship
	sf::Vector2i size = sf::Vector2i(0.f, 0.f);

	// Numbers of points in shape
	size_t pointsNum = 0;
};