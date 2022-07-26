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

	player = Ship(playerShape, ShipPhysics());

	for (int i = 0; i < enemiesNum; ++i) {
		enemies.push_back(Ship{ ShipShape(enemyTexture, shipSize, quality), ShipPhysics() });
	}

	initPlayer();
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

		mainWindow.draw(player.getShape());
		
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
	std::cout << "Input " << enemies.size()
			  << " distances, speeds and directions to enemy ships: " 
			  << std::endl;

	for (auto& enemy : enemies) {
		float speed = 0;
		float distance = 0;
		float direction = 0;
		std::cin >> distance >> speed >> direction;

		enemy.getPhysics().setSpeed(speed);
		enemiesDistances[enemy] = distance;
		enemiesDirections[enemy] = direction;
	}

	calcEnemyPositions();
}

void Helper::initPlayer() {
	std::cout << "Input your current speed and direction" << std::endl;
	float speed = 0;
	float direction = 0;
	std::cin >> speed >> direction;

	player.getPhysics().setSpeed(speed);
	player.getPhysics().setDirection(direction);

	player.getShape().setRotation(direction);
}

void Helper::calcEnemyPositions() { // TODO: Добавить вращение для врагов по направлению их движения
	sf::Vector2f position(0.f, 0.f);
	float x = 0;
	float y = 0;
	float angle = 0;

	for (auto& enemy : enemies) {

		angle = degreesToRadians(enemiesDirections[enemy]);

		x = player.getShape().getPosition().x + (sin(angle) * enemiesDistances[enemy])
			* (mainWindow.getSize().x / (mapsize));

		y = player.getShape().getPosition().y + (-cos(angle) * enemiesDistances[enemy])
			* (mainWindow.getSize().y / (mapsize));

		enemy.getShape().setPosition(sf::Vector2f(x, y));
	}
}

float degreesToRadians(const float degrees) {
	return (PI * degrees) / 180.f;
}