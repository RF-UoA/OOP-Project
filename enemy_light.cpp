#include "enemy.h"
#include "enemy_light.h"
#include <iostream>
#include <time.h>

enemy_light::enemy_light() {
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
    this->speed_bonus = (rand() % 51) - 1; //random value between 0% and 50%
    this->speed = 1 * speed_bonus;
    this->reduced_defense = (rand() % 81) - 1; //random value between 0 and 80
};

enemy_light::enemy_light(sf::Texture texture, std::string name, float x, float y, int health, int speed) {
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
    this->speed_bonus = (rand() % 51) - 1; //random value between 0% and 50%
    this->speed = speed * (100 + speed_bonus)/100; // speed in relation to 
    this->reduced_defense = (rand() % 81) - 1; //random value between 0 and 80

};

void enemy_light::take_damage(int damage) {this->health = this->health - (damage * (100 + this->reduced_defense)/100);}

int enemy_light::get_speed() {this->speed = speed * (100 + speed_bonus)/100;}

int enemy_light::get_health() {return this->health;}

int enemy_light::get_speed_bonus() {return this->speed_bonus;} // in percentage

int enemy_light::get_reduced_defense() {return this->reduced_defense;}
