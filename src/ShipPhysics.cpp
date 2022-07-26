#include "ShipPhysics.h"

ShipPhysics::ShipPhysics(const float speed, const float acceleration,
						 const float movementDirection) {

	this->speed = speed;
	this->acceleration = acceleration;

	if (checkDirection(movementDirection)) {
		this->movementDirection = movementDirection;
	}
}