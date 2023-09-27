#include "enemy.h"
#include <iostream>

enemy::enemy() {
    
    // initialise attributes for default constructor
    this->x_pos = 0;
    this->y_pos = 0;
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
    this->object = &sprite;

    this->health = 1;
    this->speed = 1;

}

enemy::enemy(sf::Texture texture, std::string name, float x, float y, int health, int speed) {

    // initialise attributes for constructor
    this->name = name;
    this->texture = texture;
    sf::Sprite sprite;
    sprite.setTexture(this->texture);
    this->object = &sprite;
    this->object->setPosition(x,y);
    this->x_pos = sprite.getPosition().x;
    this->y_pos = sprite.getPosition().y;
    this->health = health;
    this->speed = speed;

}

void enemy::take_damage(int damage) {this->health -= damage;}
