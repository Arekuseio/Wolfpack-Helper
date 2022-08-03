#pragma once
#include <SFML/Graphics.hpp>
#include "PlayerShip.h"
#include "EnemyShip.h"
#include <vector>
#include <iostream>

class Helper {
public:
	Helper(const sf::Vector2i& windowSize, const int enemiesNum, const sf::Texture& enemyTexture,
		   const sf::Texture& playerTexture, size_t quality);

	void initBackground(const sf::Texture& backgroundTexture); // TODO: Добавить инициализацию фона

	void addPlayer(const PlayerShip& player);

	void addEnemy(const EnemyShip& enemy);

	void onFrame();
private:

	void initEnemies();

	void initPlayers();

	void calcEnemyPosition(EnemyShip& enemy);

	sf::Vector2i calcShipSize(const sf::Vector2i& windowSize);

	sf::RenderWindow mainWindow;

	sf::Sprite background;

	std::vector<PlayerShip> players;

	std::vector<EnemyShip> enemies;

	// Map size in kilometeres
	float mapsize = 20.f;

	size_t shipSize = 0;
};