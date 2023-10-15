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
        enemy_heavy();
        enemy_heavy(sf::Texture texture, std::string name, float x, float y, int health, int speed);
        void take_damage(int damage);
        int get_speed();
        int get_health();
        int get_speed_reduction();
        int get_increased_defense();
};

#endif