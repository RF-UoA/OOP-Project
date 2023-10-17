#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "gameObject.h"
#include "tower.h"
#include "enemy.h"
#include <vector>

// SFML modules and libraries
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

class gameMap {
    protected:
        
        std::vector < enemy* > enemies; // encapsulates enemies
        std::vector < tower* > towers; // encapsulates towers

    public:
        gameMap(); // default constructor
        void add_tower(tower* tower); // add a tower to the game
        void spawn_enemy(enemy* enemy); // add an enemy to the game
        void remove_enemy(enemy* enemy); // remove a dead enemy
        void towers_attack(); // get all towers on the map to attack
        std::vector < enemy* > get_enemies(); // get the enemies vector
        std::vector < tower* > get_towers(); // get the towers vector
        ~gameMap(); // destructor

};

#endif