#ifndef ENEMY_HEAVY_H
#define ENEMY_HEAVY_H

// General libraries
#include <string>
#include "gameObject.h"
#include "enemy.h"

// SFML modules and libraries
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class enemy_heavy : public enemy {
    protected:
        int speed_reduction; // set reduced speed up to 20%
        int increased_defense; // randomly reduced defense up to 40%
    public:
        enemy_heavy(); // default constructor 
        enemy_heavy(sf::Texture texture, std::string name, float x, float y, int health, float speed); // regular constructor
        void take_damage(int damage); // take damage
        float get_speed(); // get enemy speed
        int get_health(); // get enemy health
        int get_speed_reduction(); // get speed reduction
        int get_increased_defense(); // get increased defense
};

#endif