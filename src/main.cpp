#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <thread>
#include "Helper.h"

int main()
{
    std::ifstream config("config.txt");
    int width = 0;
    int height = 0;
    if (config.is_open()) {
        config >> width;
        config >> height;
    }
    sf::Vector2i size(width, height);
    int enemyNum = 2;
    size_t points = 100;
    sf::Texture a;
    a.loadFromFile("img\\ship.png");
    Helper help(size, enemyNum, a, a, points);
    std::thread initThr(
        [&] {
            help.init();
        }
    );
    help.onFrame();

    initThr.join();
    return 0;
}
