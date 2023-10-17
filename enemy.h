#ifndef ENEMY_H
#define ENEMY_H

// General libraries
#include <string>
#include "gameObject.h"
#include "enemy.h"

// SFML modules and libraries
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class enemy : public gameObject {
    protected:
        int health; // enemy's health
        float speed; // enemy's speed
    
    public:
        enemy(); // default constructor
        enemy(sf::Texture texture, std::string name, float x, float y, int health, float speed); // regular constructor
        virtual void take_damage(int damage); // take damage (when an enemy is attacked)
        float get_speed(); // get the enemy's speed
        int get_health(); // get the enemy's health

};

#endif