#include "Helper.h"
#include <thread>
#include <chrono>

#ifndef  PI
#define PI 3.14159265f
#endif // ! PI


float degreesToRadians(const float degrees);
float radiansToDegrees(const float radians);

Helper::Helper(const sf::Vector2i& windowSize, const int enemiesNum, const sf::Texture& enemyTexture,
	const sf::Texture& playerTexture, size_t quality)  {

	mainWindow.create(sf::VideoMode(windowSize.x, windowSize.y), "Wolfpack Helper",
					  sf::Style::Close);

	this->enemyNum = enemiesNum;
	this->playerNum = 1;

	sf::Vector2i shipSize = calcShipSize(windowSize);

	playerShape = ShipShape(playerTexture, shipSize, quality);
	playerShape.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);
	enemyShape = ShipShape(enemyTexture, shipSize, quality);

	textFont.loadFromFile("fonts\\OxfordStreet.ttf");
	std::shared_ptr<Button> calcButton = std::shared_ptr<Button>(new Button("Calculate", { 120, 50 }, 20, sf::Color::White, sf::Color::Black));
	calcButton->setFont(textFont);
	calcButton->setPosition({ 0, 0 });
	calcButton->setClickEvent([] { std::cout << "Clicked" << '\n'; });
	calcButton->setMouseOverEvent([=] { calcButton->setBackColor(sf::Color::Cyan); });
	calcButton->setMouseNotOverEvent([=] { calcButton->setBackColor(sf::Color::White); });

	std::shared_ptr<Button> showHideButton = std::shared_ptr<Button>(new Button("Show/Hide ships", { 140, 50 }, 20, sf::Color::White, sf::Color::Black));
	showHideButton->setFont(textFont);
	showHideButton->setPosition({ windowSize.x / 2.f, 0 });
	showHideButton->setClickEvent([&] {	showShips = !showShips; });
	showHideButton->setMouseOverEvent([=] { showHideButton->setBackColor(sf::Color::Cyan); });
	showHideButton->setMouseNotOverEvent([=] { showHideButton->setBackColor(sf::Color::White); });

	buttons.push_back(calcButton);
	buttons.push_back(showHideButton);
}

void Helper::init() {
	initPlayers();
	initEnemies();
}

void Helper::onFrame() {
	while (mainWindow.isOpen()) {
		sf::Event event;
		while (mainWindow.pollEvent(event)) {

			switch (event.type) {

			case sf::Event::Closed:
				mainWindow.close();
				break;

			case sf::Event::MouseMoved:
				processMouseMove();
				break;

			case sf::Event::MouseButtonPressed:
				processMouseClick();
				break;
			}
		}
		mainWindow.clear(sf::Color::Blue);

		if (showShips) {
			drawShips();
		}

		drawButtons();

		mainWindow.display();

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void Helper::processMouseClick() {
	for (auto& b : buttons) {
		if (b->isMouseOver(mainWindow)) {
			b->onClicked();
		}
	}
}

void Helper::processMouseMove() {
	for (auto& b : buttons) {
		if (b->isMouseOver(mainWindow)) {
			b->onMouseOver();
		}
		else {
			b->onMouseNotOver();
		}
	}
}

void Helper::drawButtons() {
	for (auto& b : buttons) {
		b->drawTo(mainWindow);
	}
}

void Helper::drawShips() {
	for (auto& player : players) {
		mainWindow.draw(player.getShape());
	}

	for (auto& enemy : enemies) {
		mainWindow.draw(enemy.getShape());
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

	for (auto& player : players) {

		std::cout << "Input " 
			<< enemyNum
			<< " distances (km.), speeds (kn.) and directions (deg.) to enemy ships from player number "
			<< playerNum << " :"
			<< std::endl;

		for (int i = 0; i < enemyNum; ++i) {
			enemies.push_back(EnemyShip{ enemyShape, ShipPhysics() });

			std::cin >> distance >> speed >> direction;

			player.setDistanceToEnemy(enemies[i], distance);
			player.setDirectionToEnemy(enemies[i], direction);

			calcEnemyPosition(enemies[i]);

			enemies[i].getPhysics().setSpeed(speed);

			enemies[i].setDistanceFromPlayer(player, distance);
			enemies[i].setDirectionFromPlayer(player, direction);
		}
	}

	int enemynum = 1;
	float realSize = 0;
	float relativeSize = 0;
	bool from = false;

	for (auto& enemy : enemies) {
		std::cout << "Input the real length (m.) of enemy number " << enemynum
			<< ", length looking from the first ship and direction (deg.) of movement (0/1 (at you, from you))" << std::endl;

		std::cin >> realSize >> relativeSize >> from;

		calcEnemyDirection(enemy, realSize, relativeSize, from);
		enemynum++;
	}
}

void Helper::initPlayers() {
	std::cout << "Input " << playerNum << " current speeds (kn.) and directions (deg.)" << std::endl;
	float speed = 0;
	float direction = 0;

	for (int i = 0; i < playerNum; ++i) {
		std::cin >> speed >> direction;
		players.push_back({ playerShape, ShipPhysics(speed, 0, direction) });
		players[i].getShape().setRotation(direction);
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