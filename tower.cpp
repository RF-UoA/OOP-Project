#include "tower.h"
#include <iostream>

tower::tower() {

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

tower::tower(sf::Texture texture, std::string name, float x, float y) {
        
    // initialise attributes for constructor
    this->name = name;
    this->texture = texture;
    sf::Sprite sprite;
    sprite.setTexture(this->texture);
    this->object = &sprite;
    this->object->setPosition(x,y);
    this->x_pos = sprite.getPosition().x;
    this->y_pos = sprite.getPosition().y;

}

// attack is a virtual function and will apply to towers individually

void tower::attack(enemy** enemy, int num_enemies) {

    for (int i=0; i<num_enemies; i++) {
        enemy[i]->take_damage(0);
    }
}