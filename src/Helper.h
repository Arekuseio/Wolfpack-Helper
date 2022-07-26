#pragma once
#include <SFML/Graphics.hpp>
#include "Ship.h"
#include <vector>
#include <iostream>

class Helper {
public:
	Helper(const sf::Vector2i& windowSize, const int enemiesNum, const sf::Texture& enemyTexture,
		   const sf::Texture& playerTexture, size_t quality);

	void onFrame();
private:

	void initEnemies();

	void initPlayer();

	void calcEnemyPositions();

	sf::Vector2i calcShipSize(const sf::Vector2i& windowSize);

	sf::RenderWindow mainWindow;

	Ship player;

	std::vector<Ship> enemies;

	// Distances between player and enemies
	std::map<Ship, float> enemiesDistances;

	// Directions to enemies, relative to the player ship
	std::map<Ship, float> enemiesDirections;

	// Map size in kilometeres
	float mapsize = 20.f;

	size_t shipSize = 0;
};