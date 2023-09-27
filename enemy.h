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
        int health;
        int speed;
    
    public:
        enemy();
        enemy(sf::Texture texture, std::string name, float x, float y, int health, int speed);
        void take_damage(int damage);

};

#endif