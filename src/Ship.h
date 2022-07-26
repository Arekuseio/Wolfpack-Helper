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

	bool operator<(const Ship& other) const {
		return physics.getSpeed() < other.physics.getSpeed();
	}

private:
	ShipShape shape;

	ShipPhysics physics;
};