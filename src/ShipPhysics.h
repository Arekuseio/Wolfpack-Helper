#pragma once


class ShipPhysics {
public:
	explicit ShipPhysics(const float speed, const float acceleration,
				const float movementDirection);

	ShipPhysics() { }

	float getSpeed() const {
		return speed;
	}

	float getAcceleration() const {
		return acceleration;
	}

	float getDirection() const {
		return movementDirection;
	}

	void setSpeed(const float new_speed) {
		speed = new_speed;
	}

	void setAcceleration(const float new_acceleration) {
		acceleration = new_acceleration;
	}

	bool setDirection(const float new_direction) {
		if (checkDirection(new_direction)) {
			movementDirection = new_direction;
			return true;
		} else {
			return false;
		}
	}

	bool checkDirection(const float dir) {
		return (dir <= 360.f && dir >= 0);
	}

private:

	// Speed in knots
	float speed = 0.f;

	float acceleration = 0.f;

	// Direction, relative to this ship (deg.), must be in interval [0, 360]
	float movementDirection = 0.f;
};