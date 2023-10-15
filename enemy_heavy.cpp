#include "enemy.h"
#include "enemy_heavy.h"
#include <iostream>
#include <time.h>

enemy_heavy::enemy_heavy() {
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
    this->speed_reduction = (rand() % 21) - 1; //random value between 0% and 20%
    this->speed = 1 - (1 * ((speed_reduction)/100));
    this->increased_defense = (rand() % 41) - 1; //random value between 0 and 40%
};

enemy_heavy::enemy_heavy(sf::Texture texture, std::string name, float x, float y, int health, int speed) {
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
    this->speed_reduction = (rand() % 21) - 1; //random value between 0% and 20%
    this->speed = speed - (speed * ((speed_reduction)/100));
    this->increased_defense = (rand() % 41) - 1; //random value between 0 and 40%

};

void enemy_heavy::take_damage(int damage) {
    this->health = this->health - (damage - (damage * (this->increased_defense)/100));
};

int enemy_heavy::get_speed() {return this->speed;}

int enemy_heavy::get_health() {return this->health;}

int enemy_heavy::get_speed_reduction() {return this->speed_reduction;} // in percentage

int enemy_heavy::get_increased_defense() {return this->increased_defense;}
