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
        enemy_light();
        enemy_light(sf::Texture texture, std::string name, float x, float y, int health, float speed);
        void take_damage(int damage);
        float get_speed();
        int get_health();
        int get_speed_bonus();
        int get_reduced_defense();
};

#endif