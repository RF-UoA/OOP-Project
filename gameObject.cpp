#include "gameObject.h"
#include <iostream>

gameObject::gameObject() {
    
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

}

gameObject::gameObject(sf::Texture texture, std::string name) {
    
    // initialise attributes for constructor
    this->name = name;
    this->texture = texture;
    sf::Sprite sprite;
    sprite.setTexture(this->texture);
    this->object = &sprite;
    this->x_pos = sprite.getPosition().x;
    this->y_pos = sprite.getPosition().y;


}

float gameObject::get_x() {return this->object->getPosition().x;}

float gameObject::get_y() {return this->object->getPosition().y;}

void gameObject::set_texture(sf::Texture texture) {

    this->texture = texture;
    this->object->setTexture(this->texture);

}

void gameObject::set_name(std::string name) {this->name = name;}

std::string gameObject::get_name() {return this->name;}

sf::Sprite* gameObject::get_object() {return this->object;}
