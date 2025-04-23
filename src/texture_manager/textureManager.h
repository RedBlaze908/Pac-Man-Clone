#pragma once
#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>

class TextureManager {
	std::map<int8_t, sf::Texture> map;

public:

	TextureManager();
	~TextureManager();

	sf::Texture* getTexture(int8_t val);
};