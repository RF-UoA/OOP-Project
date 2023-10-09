#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "gameObject.h"
#include "tower.h"
#include "enemy.h"
#include "tile.h"
#include <vector>

// SFML modules and libraries
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

class gameMap {

    protected:
        
        std::vector < enemy* > enemies;
        std::vector < tower * > towers;

    public:
        gameMap();
        void add_tower(tower* tower);
        void spawn_enemy(enemy* enemy);
        void remove_enemy(enemy* enemy);
        void towers_attack();
        void move_enemies();
        std::vector < enemy* > get_enemies();
        std::vector < tower* > get_towers();
        ~gameMap();

};

#endif