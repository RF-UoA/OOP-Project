#include "tower.h"
#include <iostream>
#include <cmath>

tower::tower() {

    // initialise attributes for default constructor
    this->range = 0;
    this->pos.x = 0.0f;
    this->pos.y = 0.0f;
    this->name = "NA";
    this->attacking = 0;
    this->type = 0;

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

}

tower::tower(sf::Texture texture, std::string name, float x, float y) {
        
    // initialise attributes for constructor
    this->name = name;
    this->texture = texture;
    this->attacking = 0;
    this->type = 0;
    sf::Sprite sprite;
    sprite.setTexture(this->texture);
    sf::Vector2f desiredSize(80.0f, 80.0f); // Replace with your desired size

    // Calculate the scaling factors
    float scaleX = desiredSize.x / this->texture.getSize().x;
    float scaleY = desiredSize.y / this->texture.getSize().y;

    // Set the scale of the sprite to achieve the desired size in pixels
    sprite.scale(sf::Vector2f(scaleX, scaleY));
    this->object = sprite;
    this->pos.x = x;
    this->pos.y = y;
    this->object.setPosition(this->pos);
    this->attacking = 0; // Number of frames that attack is visible for
    this->type = 0;
    this->range = 0;

}

int tower::get_type() {return this->type;}

int tower::get_attacking() {return this->attacking;}

void tower::set_attacking(int attacking) {this->attacking = attacking;}

int tower::get_range() {return this->range;}