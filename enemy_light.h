#ifndef ENEMY_LIGHT_H
#define ENEMY_LIGHT_H

// General libraries
#include <string>
#include "gameObject.h"
#include "enemy.h"

// SFML modules and libraries
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class enemy_light : public enemy {
    protected:
        int speed_bonus; // set additional speed in % up to 50%
        int reduced_defense; // randomly reduced defense in % up to 80%
    public:
        enemy_light(); // default constructor 
        enemy_light(sf::Texture texture, std::string name, float x, float y, int health, float speed); // regular constructor 
        void take_damage(int damage); // take damage
        float get_speed(); // get speed
        int get_health(); // get health
        int get_speed_bonus(); // get speed bonus
        int get_reduced_defense(); // get reduced defense
};

#endif