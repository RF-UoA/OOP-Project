#include "tile.h"
#include <iostream>

// tile::tile() {
    
//     // initialise attributes for default constructor
//     this->pos.x = 0.0f;
//     this->pos.y = 0.0f;
//     this->name = "NA";

//     // attempt to create blank 16 x 16 texture
//     sf::Texture texture;
//     if (!texture.create(100, 100)) {
//         // error handling
//         std::cout << "error loading exture" << std::endl; 
//     }

//     // define texture and object
//     this->texture = texture;
//     sf::Sprite sprite;
//     sprite.setTexture(this->texture);
//     this->object = sprite;
//     this->path = 0;

// }

// tile::tile(sf::Texture texture, std::string name, float x, float y, bool path) {
    
//     // initialise attributes for constructor
//     this->name = name;
//     this->texture = texture;
//     sf::Sprite sprite;
//     sprite.setTexture(this->texture);
//     sprite.setTextureRect(sf::IntRect(0,0,100,100));
//     this->object = sprite;
//     this->pos.x = x;
//     this->pos.y = y;
//     this->object.setPosition(this->pos);
//     this->path = path;

// }

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