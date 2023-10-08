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
    void setUpInitialState();
    void setUpTiles();

    protected:
        
        int total_num;
        int num_towers;
        int num_enemies;
        int num_tiles;
        gameObject** all_objects;
        // tower** towers;
        // enemy** enemies;
        std::vector < enemy* > enemies;
        std::vector < tower * > towers;

    public:
        gameMap();
        void add_tower(tower* tower);
        void spawn_enemy(enemy* enemy);
        void remove_enemy(enemy* enemy);
        void towers_attack();
        void move_enemies();
        int get_num_enemies();
        std::vector < enemy* > get_enemies();
        std::vector < tower* > get_towers();
        ~gameMap();

};

#endif