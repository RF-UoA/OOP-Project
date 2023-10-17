#include "tile.h"
#include <iostream>

// this file is redundant

tile::tile(std::string textureName, float x, float y, bool passable, bool exit) {
    if (!setUpSprite(textureName)) {
        return;
    }

    pos = sf::Vector2f(x,y);
    sprite.setPosition(pos);
    isPassable = passable;
    isExit = exit;
}

bool tile::setUpSprite(std::string textureName) {
    if (!texture.loadFromFile(textureName)) {
        return false;
    }

    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0,0,100,100));
    return true;
}