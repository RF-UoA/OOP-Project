#include "gameObject.h"
#include <iostream>

// Defualt constructor
gameObject::gameObject() {
    
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

}

// regular constructor
gameObject::gameObject(sf::Texture texture, std::string name, float x, float y) {
    
    // initialise attributes for constructor
    this->name = name;
    this->texture = texture;
    sf::Sprite sprite;
    sprite.setTexture(this->texture);
    
    // Define the disired size for sprite dimensions
    sf::Vector2f desiredSize(80.0f, 80.0f);

    // Calculate the scaling factors
    float scaleX = desiredSize.x / texture.getSize().x;
    float scaleY = desiredSize.y / texture.getSize().y;

    // Set the scale of the sprite to achieve the desired size in pixels
    sprite.setScale(scaleX, scaleY);
    this->object = sprite;
    this->pos.x = x;
    this->pos.y = y;
    this->object.setPosition(this->pos);

}

// returns the position of the object's sprite
sf::Vector2f gameObject::get_pos() {return this->object.getPosition();}

// set the position of the object and update pos variable
void gameObject::set_pos(sf::Vector2f pos) {this->pos = pos; this->object.setPosition(this->pos);}

// set the texture of the object's sprite
void gameObject::set_texture(sf::Texture texture) {

    this->texture = texture;
    this->object.setTexture(this->texture);

}

// set the object's name
void gameObject::set_name(std::string name) {this->name = name;}

// return the object's name
std::string gameObject::get_name() {return this->name;}

// get the sprite of the object
sf::Sprite gameObject::get_object() {return this->object;}

// move the object's sprite
void gameObject::moveObject(sf::Vector2f movement) {this->object.move(movement);}
