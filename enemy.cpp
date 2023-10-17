#include "enemy.h"
#include <iostream>

// default constructor. Only exists as a precaution
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

// regular constructor
enemy::enemy(sf::Texture texture, std::string name, float x, float y, int health, float speed) {

    // initialise attributes for constructor
    this->name = name;
    this->texture = texture;
    sf::Sprite sprite;
    sprite.setTexture(this->texture);
    sprite.scale(0.2,0.2); // scale the texture
    this->object = sprite;
    this->pos.x = x;
    this->pos.y = y;
    this->object.setPosition(this->pos); // update sprite's position
    this->health = health;
    this->speed = speed;

}

// reduce the health of an enemy when taking damage
void enemy::take_damage(int damage) {this->health -= damage;}

// return speed
float enemy::get_speed() {return this->speed;}

// return health
int enemy::get_health() {return this->health;}