#pragma once
#include <SFML/Graphics.hpp>
#include "PlayerShip.h"
#include "EnemyShip.h"
#include "Button.h"
#include <vector>
#include <iostream>
#include <memory>

class Helper {
public:
	Helper(const sf::Vector2i& windowSize, const int enemiesNum, const sf::Texture& enemyTexture,
		   const sf::Texture& playerTexture, size_t quality);

	void initBackground(const sf::Texture& backgroundTexture); // TODO: Добавить инициализацию фона

	void addPlayer(const PlayerShip& player);
	void addEnemy(const EnemyShip& enemy);

	void init();

	void onFrame();
private:

	int enemyNum;
	int playerNum;

	ShipShape playerShape;
	ShipShape enemyShape;

	void initEnemies();
	void initPlayers();
	void calcEnemyPosition(EnemyShip& enemy);
	void drawShips();
	void drawButtons();

	void processMouseMove();
	void processMouseClick();

	// Calculating enemy ship direction using his real length and relative length
	void calcEnemyDirection(EnemyShip& enemy, const float realLength, const float relativeLength, bool from);

	sf::Vector2i calcShipSize(const sf::Vector2i& windowSize);

	sf::RenderWindow mainWindow;

	sf::Sprite background;

	std::vector<PlayerShip> players;
	std::vector<EnemyShip> enemies;

	// Map size in kilometeres
	float mapsize = 20.f;

	size_t shipSize = 0;

	bool showShips = true;

	std::vector<std::shared_ptr<Button>> buttons;

	sf::Font textFont;
};