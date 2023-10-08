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
        
        int num_grids;
        int grid_length;
        int total_num;
        int num_towers;
        int num_enemies;
        int num_tiles;
        gameObject** all_objects;
        tower** towers;
        // tile** tiles;
        enemy** enemies;

    public:
        std::vector < std::vector < tile* >> tiles;
        gameMap();
        void add_tower(tower* tower);
        void spawn_enemy(enemy* enemy);
        void remove_enemy(enemy* enemy);
        void towers_attack();
        void generate_path();
        void move_enemies();

};

#endif