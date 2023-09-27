#ifndef MAP_H
#define MAP_H

#include "gameObject.h"
#include "tower.h"

// SFML modules and libraries
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class map {
    protected:
        sf::Sprite** all_objects;
        sf::Sprite** towers;
        sf::Sprite** paths;
        sf::Sprite** groud;

    public:
        map();
        void add_tower(tower* tower);
        void spawn_enemy(enemy* enemy);
        void remove_enemy(enemy* enemy);
        void towers_attack();
        void generate_path();

};

#endif