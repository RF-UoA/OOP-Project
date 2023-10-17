#ifndef TOWER_H
#define TOWER_H

// General libraries
#include <string>
#include "gameObject.h"
#include "enemy.h"

// SFML modules and libraries
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class tower : public gameObject { // abstract class
    protected:
        int type; // type of tower
        int attacking; // attacking period for physically drawing attacks
        int range; // range of tower
    public:
        tower(); // default constructor
        tower(sf::Texture texture, std::string name, float x, float y); // regular constructor
        virtual void attack(std::vector < enemy* > enemies) = 0; // PURE virtual function, attack enemies
        int get_type(); // get type of tower
        int get_attacking(); // get attacking period
        int get_range(); // get tower range
        void set_attacking(int attacking); // set attacking period

};

#endif