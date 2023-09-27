#ifndef MAP_H
#define MAP_H

#include "gameObject.h"
#include "tower.h"
#include "enemy.h"

// SFML modules and libraries
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class map {
    protected:
        int total_num;
        int num_towers;
        int num_enemies;
        int num_paths;
        gameObject** all_objects;
        tower** towers;
        gameObject** paths;
        enemy** enemies;
        gameObject** groud;

    public:
        map();
        void add_tower(tower* tower);
        void spawn_enemy(enemy* enemy);
        void remove_enemy(enemy* enemy);
        void towers_attack();
        void generate_path();
        void move_enemies();

};

#endif