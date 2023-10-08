#include "gameObject.h"
#include <iostream>

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

gameObject::gameObject(sf::Texture texture, std::string name, float x, float y) {
    
    // initialise attributes for constructor
    this->name = name;
    this->texture = texture;
    sf::Sprite sprite;
    sprite.setTexture(this->texture);
    this->object = sprite;
    this->pos.x = x;
    this->pos.y = y;
    this->object.setPosition(this->pos);

}

sf::Vector2f gameObject::get_pos() {return this->pos;}

void gameObject::set_pos(sf::Vector2f pos) {this->pos = pos; this->object.setPosition(this->pos);}

void gameObject::set_texture(sf::Texture texture) {

    this->texture = texture;
    this->object.setTexture(this->texture);

}

void gameObject::set_name(std::string name) {this->name = name;}

std::string gameObject::get_name() {return this->name;}

sf::Sprite gameObject::get_object() {return this->object;}

void gameObject::moveObject(sf::Vector2f movement) {this->object.move(movement);}
