#ifndef AOETOWER_H
#define AOETOWER_H

// General libraries
#include <string>
#include "gameObject.h"
#include "tower.h"
#include "enemy.h"

// SFML modules and libraries
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class AOETower : public tower {
    public:
        AOETower();
        AOETower(sf::Texture texture, std::string name, float x, float y);
        void attack(std::vector < enemy* > enemies);

};

#endif