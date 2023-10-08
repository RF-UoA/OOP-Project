#include "enemy.h"
#include <iostream>

enemy::enemy() {
    
    // initialise attributes for default constructor
    this->pos.x = 0.0f;
    this->pos.y = 0.0f;
    this->name = "NA";

    // attempt to create blank 16 x 16 texture
    sf::Texture texture;
    if (!texture.create(16, 16)) {
        // error handling
        std::cout << "error loading exture" << std::endl; 
    }

    // define texture and object
    this->texture = texture;
    sf::Sprite sprite;
    sprite.setTexture(this->texture);
    this->object = sprite;

    this->health = 1;
    this->speed = 1;

}

enemy::enemy(sf::Texture texture, std::string name, float x, float y, int health, int speed) {

    // initialise attributes for constructor
    this->name = name;
    this->texture = texture;
    sf::Sprite sprite;
    sprite.setTexture(this->texture);
    this->object = sprite;
    this->pos.x = x;
    this->pos.y = y;
    this->object.setPosition(this->pos);
    this->health = health;
    this->speed = speed;

}

void enemy::take_damage(int damage) {this->health -= damage;}
