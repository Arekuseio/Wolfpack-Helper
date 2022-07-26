#include "Ship.h"

Ship::Ship(const ShipShape& shape, const ShipPhysics& physics) {

	this->shape = shape;
	this->physics = physics;
}