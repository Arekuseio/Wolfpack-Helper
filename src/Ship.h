#pragma once

#include "ShipPhysics.h"
#include "ShipShape.h"

class Ship {
public:
	Ship(const ShipShape& shape, const ShipPhysics& physics);

	Ship() { }

	ShipShape& getShape() {
		return shape;
	}

	ShipPhysics& getPhysics() {
		return physics;
	}

	sf::Vector2f getPosition() const {
		return shape.getPosition();
	}

	bool operator<(const Ship& other) const {
		return (this->getPosition() != other.getPosition())
			&& (this->getPosition().x < other.getPosition().x);
	}

private:
	ShipShape shape;

	ShipPhysics physics;
};