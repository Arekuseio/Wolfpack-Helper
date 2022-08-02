#pragma once

#include "Ship.h"

class EnemyShip;

class PlayerShip : public Ship {

public:
	PlayerShip(const ShipShape& shape, const ShipPhysics& physics)
				: Ship(shape, physics) {  };

	PlayerShip() { };

	float getDistanceToEnemy(const EnemyShip& enemy) {
		return distanceToEnemy[enemy];
	}

	void setDistanceToEnemy(const EnemyShip& enemy, float distance) {
		distanceToEnemy[enemy] = distance;
	}

	float getDirectionToEnemy(const EnemyShip& enemy) {
		return directionToEnemy[enemy];
	}

	void setDirectionToEnemy(const EnemyShip& enemy, float direction) {
		if (this->getPhysics().checkDirection(direction))
			directionToEnemy[enemy] = direction;
	}

private:

	// Distances from this player to any enemy ship
	std::map<EnemyShip, float> distanceToEnemy;


	// Directions from this player to any enemy ship
	std::map<EnemyShip, float> directionToEnemy;
};