#ifndef ENEMY_MEDIUM_H
#define ENEMY_MEDIUM_H

// General libraries
#include <string>
#include "gameObject.h"
#include "enemy.h"

// SFML modules and libraries
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class enemy_medium : public enemy {
    protected:
        int dodge_chance; // random chance to avoid damage (0% - 7%)
    public:
        enemy_medium();
        enemy_medium(sf::Texture texture, std::string name, float x, float y, int health, int speed);
        void take_damage(int damage);
        int get_speed();
        int get_health();
        int get_dodge_chance();
};

#endif