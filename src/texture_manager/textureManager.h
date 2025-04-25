#pragma once
#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <iostream>

/*
	-1 = player
	0 = empty floor
	1 = floor with food
	2 = vertical wall
	3 = orizontal wall
	4 = corner 1
	5 = corner 2
	6 = corner 3
	7 = corner 4

*/

class TextureManager {
	std::map<int8_t, sf::Texture> map;

	void checkTextureExist(sf::Texture* t);
public:

	TextureManager();
	~TextureManager();

	sf::Texture* getTexture(int8_t val);
};