#include "tower.h"
#include <iostream>
#include <cmath>

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

void tower::attack(std::vector < enemy* > enemies) {

    // method 0 (default)
    // for (int i=0; i<enemies.size(); i++) {
    //     enemies[i]->take_damage(1);
    //     std::cout << this->name << " Successfully attacked an enemy!" << std::endl;
    // }

    // method 1
    // if (enemies.size() > 0) {
    //     enemies[0]->take_damage(1);
    //     std::cout << this->name << " Successfully attacked an enemy! Enemy now has " << enemies[0]->get_health() << " health" << std::endl;
    // }

    // method 2
    for (int i=0; i<enemies.size(); i++) {
        sf::Vector2f enemy_position = enemies[i]->get_object().getPosition();
        sf::Vector2f displacement = enemy_position - this->pos;
        float distance = pow(pow(displacement.x,2)+pow(displacement.y,2),0.5);

        float range = 300;

        if (distance <= range) {
            enemies[i]->take_damage(1);
            std::cout << this->name << " Successfully attacked an enemy! Enemy now has " << enemies[i]->get_health() << " health" << std::endl;
        }
    }

}