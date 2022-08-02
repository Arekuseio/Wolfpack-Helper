#pragma once

#include "Ship.h"

class PlayerShip;

class EnemyShip : public Ship {

public:
	EnemyShip(const ShipShape& shape, const ShipPhysics& physics) 
				: Ship(shape, physics) {  };

	EnemyShip() { };

	float getDistanceFromPlayer(const PlayerShip& player) {
		return distanceFromPlayer[player];
	}

	void setDistanceFromPlayer(const PlayerShip& player, const float distance) {
		distanceFromPlayer[player] = distance;
	}

	float getDirectionFromPlayer(const PlayerShip& player) {
		return directionFromPlayer[player];
	}

	void setDirectionFromPlayer(const PlayerShip& player, float direction) {
		if (this->getPhysics().checkDirection(direction))
			directionFromPlayer[player] = direction;
	}

private:

	void calcPosition();

	// Distances to this enemy ship from any player ship
	std::map<PlayerShip, float> distanceFromPlayer;

	// Directions to this enemt ship from any player ship
	std::map<PlayerShip, float> directionFromPlayer;
};