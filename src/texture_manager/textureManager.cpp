#include "textureManager.h"

void TextureManager::checkTextureExist(sf::Texture* t) {
	if (!t) {
		std::cerr << "Error: Texture Not Found!" << std::endl;
		exit(EXIT_FAILURE);
	}
}

TextureManager::TextureManager() {
	sf::Texture t;
	t.loadFromFile("../../../src/assets/player.png");
	TextureManager::checkTextureExist(&t);
	map[-1] = t;
	t.loadFromFile("../../../src/assets/empty.png");
	TextureManager::checkTextureExist(&t);
	map[0] = t;
	t.loadFromFile("../../../src/assets/wall2.png");
	TextureManager::checkTextureExist(&t);
	map[2] = t;
	t.loadFromFile("../../../src/assets/wall.png");
	TextureManager::checkTextureExist(&t);
	map[3] = t;
	t.loadFromFile("../../../src/assets/corner1.png");
	TextureManager::checkTextureExist(&t);
	map[4] = t;
	t.loadFromFile("../../../src/assets/corner2.png");
	TextureManager::checkTextureExist(&t);
	map[5] = t;
	t.loadFromFile("../../../src/assets/corner3.png");
	TextureManager::checkTextureExist(&t);
	map[6] = t;
	t.loadFromFile("../../../src/assets/corner4.png");
	TextureManager::checkTextureExist(&t);
	map[7] = t;
}

TextureManager::~TextureManager() {}

sf::Texture* TextureManager::getTexture(int8_t val) {
    auto it = map.find(val);

    if (it != map.end()) return &it->second;
    else return nullptr;
}
