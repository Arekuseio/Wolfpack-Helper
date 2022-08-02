#include "Helper.h"

#ifndef  PI
#define PI 3.14159265
#endif // ! PI


float degreesToRadians(const float degrees);

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
		mainWindow.clear();

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

	float xSize = windowSize.x / (50.f * relation);

	float ySize = windowSize.y / (20.f * relation);

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

			// —начала ввод данных, затем по ним расчет позиции врага

			std::cin >> distance >> speed >> direction;

			player.setDistanceToEnemy(enemy, distance);
			player.setDirectionToEnemy(enemy, direction);


			// TODO: »справить то что позици€ просчитываетс€ заново дл€ каждого игрока
			calcEnemyPosition(enemy);

			enemy.getPhysics().setSpeed(speed);
			
			enemy.setDistanceFromPlayer(player, distance);
			enemy.setDirectionFromPlayer(player, direction);
		}
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

void Helper::calcEnemyPosition(EnemyShip& enemy) { // TODO: ƒобавить вращение дл€ врагов по направлению их движени€
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

float degreesToRadians(const float degrees) {
	return (PI * degrees) / 180.f;
}