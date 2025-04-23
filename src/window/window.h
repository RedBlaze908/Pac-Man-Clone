#pragma once
#include "imgui.h"
#include "imgui-SFML.h"
#include "../texture_manager/textureManager.h"
#include <iostream>
#include <vector>

const float cellSize = 38.f;
const int cols = 25;
const int rows = 25;

struct tile {
	int8_t val;
	sf::RectangleShape t;
};

struct data {
	int x;
	int y;
};

class Game {
	std::vector<std::vector<tile>> grid;
	sf::RenderWindow window;

	sf::Clock deltaClock;
	sf::Clock clock;
	sf::Clock btnClock;
	sf::Event event;
	/*sf::Text score;
	int Score = 0;
	bool over = false;*/

	TextureManager texture;
	data playerPos{12, 12};

	void makeGrid();

	void playerSpawn();

	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();


public:
	Game();
	~Game();

	void init();
	
};