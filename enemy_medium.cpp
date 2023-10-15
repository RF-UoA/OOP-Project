#include "enemy.h"
#include "enemy_medium.h"
#include <iostream>
#include <time.h>

enemy_medium::enemy_medium() {
    // random values dependent on time
    srand(time(NULL));
        
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
    this->dodge_chance = (rand() % 8) - 1; //random value between 0 and 7
};

enemy_medium::enemy_medium(sf::Texture texture, std::string name, float x, float y, int health, float speed) {
    // random values dependent on time
    srand(time(NULL));
    
    // initialise attributes for constructor
    this->name = name;
    this->texture = texture;
    sf::Sprite sprite;
    sprite.setTexture(this->texture);
    sprite.scale(0.2,0.2);
    this->object = sprite;
    this->pos.x = x;
    this->pos.y = y;
    this->object.setPosition(this->pos);
    this->health = health;
    this->speed = speed;
    this->dodge_chance = (rand() % 8) - 1; //random value between 0 and 7

};

void enemy_medium::take_damage(int damage) {
    // randomise seed
    srand(time(NULL));
    
    // only take damage if a random value exceeds dodge chance
    if ((rand() % 10) - 1 > this->dodge_chance) {
        this->health = this->health - damage;
    } else {
        // take no damage
        this->health = this->health;
    }
}

float enemy_medium::get_speed() {return this->speed;}

int enemy_medium::get_health() {return this->health;}

int enemy_medium::get_dodge_chance() {return this->dodge_chance;} // in percentage
