#include "Helper.h"

#ifndef  PI
#define PI 3.14159265
#endif // ! PI


float degreesToRadians(const float degrees);
float radiansToDegrees(const float radians);

Helper::Helper(const sf::Vector2i& windowSize, const int enemiesNum, const sf::Texture& enemyTexture,
			   const sf::Texture& playerTexture, size_t quality) {

	mainWindow.create(sf::VideoMode(windowSize.x, windowSize.y), "Wolfpack Helper",
					  sf::Style::Close);

	sf::Vector2i shipSize = calcShipSize(windowSize);

	ShipShape playerShape = ShipShape(playerTexture, shipSize, quality);
	playerShape.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);

	players.push_back(PlayerShip(playerShape, ShipPhysics()));

	for (int i = 0; i < enemiesNum; ++i) {
		enemies.push_back(EnemyShip{ ShipShape(enemyTexture, shipSize, quality), ShipPhysics() });
	}

	initPlayers();
	initEnemies();
}

void Helper::onFrame() {
	while (mainWindow.isOpen()) {
		sf::Event event;
		while (mainWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				mainWindow.close();
		}
		mainWindow.clear(sf::Color::Blue);

		for (auto& player : players) {
			mainWindow.draw(player.getShape());
		}
		
		for (auto& enemy : enemies) {
			mainWindow.draw(enemy.getShape());
		}

		mainWindow.display();
	}
}

sf::Vector2i Helper::calcShipSize(const sf::Vector2i& windowSize) {

	float relation = windowSize.x / windowSize.y;

	float xSize = windowSize.x / (25.f * relation);

	float ySize = windowSize.y / (10.f * relation);

	return sf::Vector2i(xSize, ySize);
}

void Helper::initEnemies() {

	float speed = 0;
	float distance = 0;
	float direction = 0;

	int playerNum = 1;

	for (auto& player : players) {

		std::cout << "Input " 
			<< enemies.size()
			<< " distances, speeds and directions to enemy ships from player number "
			<< playerNum << " :"
			<< std::endl;

		for (auto& enemy : enemies) {

			// Сначала ввод данных, затем по ним расчет позиции врага

			std::cin >> distance >> speed >> direction;

			player.setDistanceToEnemy(enemy, distance);
			player.setDirectionToEnemy(enemy, direction);

			calcEnemyPosition(enemy);

			enemy.getPhysics().setSpeed(speed);
			
			enemy.setDistanceFromPlayer(player, distance);
			enemy.setDirectionFromPlayer(player, direction);

			
		}
	}

	int enemynum = 1;
	float realSize = 0;
	float relativeSize = 0;
	bool from = false;

	for (auto& enemy : enemies) {
		std::cout << "Input the real length of enemy number " << enemynum
			<< ", length relative to the first ship and direction of movement (0/1 (at you, from you))" << std::endl;

		std::cin >> realSize >> relativeSize >> from;

		calcEnemyDirection(enemy, realSize, relativeSize, from);
		enemynum++;
	}
}

void Helper::initPlayers() {
	std::cout << "Input " << players.size() << " current speeds and directions" << std::endl;
	float speed = 0;
	float direction = 0;

	for (auto& player : players) {
		std::cin >> speed >> direction;

		player.getPhysics().setSpeed(speed);
		player.getPhysics().setDirection(direction);

		player.getShape().setRotation(direction);
	}
}

void Helper::calcEnemyPosition(EnemyShip& enemy) {
	if (enemy.getPosition() == sf::Vector2f(0.f, 0.f)) {
		sf::Vector2f position(0.f, 0.f);
		float x = 0;
		float y = 0;
		float angle = 0;
		angle = degreesToRadians(players[0].getDirectionToEnemy(enemy));

		x = players[0].getShape().getPosition().x + (sin(angle) * players[0].getDistanceToEnemy(enemy))
			* (mainWindow.getSize().x / (mapsize));

		y = players[0].getShape().getPosition().y + (-cos(angle) * players[0].getDistanceToEnemy(enemy))
			* (mainWindow.getSize().y / (mapsize));

		enemy.getShape().setPosition(sf::Vector2f(x, y));
	}
}


void Helper::calcEnemyDirection(EnemyShip& enemy, const float realSize, const float relativeSize, const bool from) {

	float directToEnemy = players[0].getDirectionToEnemy(enemy);

	float alpha = acos(relativeSize / realSize);
	alpha = radiansToDegrees(alpha);

	
	float direction = 0;

	if (from) {
		direction = 90.f - alpha + directToEnemy;
	} else {
		direction = 270.f - alpha + directToEnemy;
	}
	enemy.getPhysics().setDirection(direction);
	enemy.getShape().setRotation(direction);
}

float degreesToRadians(const float degrees) {
	return (PI * degrees) / 180.f;
}

float radiansToDegrees(const float radians) {
	return (180.f * radians) / PI;
}