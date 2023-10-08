#include "tower.h"
#include <iostream>

tower::tower() {

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

tower::tower(sf::Texture texture, std::string name, float x, float y) {
        
    // initialise attributes for constructor
    this->name = name;
    this->texture = texture;
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

}

// attack is a virtual function and will apply to towers individually

void tower::attack(enemy** enemies, int num_enemies) {

    for (int i=0; i<num_enemies; i++) {
        enemies[i]->take_damage(0);
    }
}