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

class tower : public gameObject {
    protected:
        int type;
        int attacking;
        int range;
    public:
        tower();
        tower(sf::Texture texture, std::string name, float x, float y);
        virtual void attack(std::vector < enemy* > enemies) = 0;
        int get_type();
        int get_attacking();
        int get_range();
        void set_attacking(int attacking);

};

#endif