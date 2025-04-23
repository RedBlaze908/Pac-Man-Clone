#include "textureManager.h"

TextureManager::TextureManager() {
	sf::Texture t;
	t.loadFromFile("../../../src/assets/player.png");

	map[-1] = t;
}

TextureManager::~TextureManager() {}

sf::Texture* TextureManager::getTexture(int8_t val) {
    auto it = map.find(val);

    if (it != map.end()) return &it->second;
    else return nullptr;
}
