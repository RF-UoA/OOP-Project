#ifndef RANGEDTOWER_H
#define RANGEDTOWER_H

// General libraries
#include <string>
#include "gameObject.h"
#include "tower.h"
#include "enemy.h"

// SFML modules and libraries
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class rangedTower : public tower {
    public:
        rangedTower(); // default constructor
        rangedTower(sf::Texture texture, std::string name, float x, float y); // regular constructor
        void attack(std::vector < enemy* > enemies); // attack function

};

#endif