#include <iostream>

// SFML modules and libraries
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "gameObject.h"
#include "tower.h"
#include "AOETower.h"
#include "rangedTower.h"
#include "gameMap.h"
#include "enemy.h"


int main(void) {

    // load textures
    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile("images/enemy.png")) {
        return 1;
    }

    sf::Texture towerTexture;
    if (!towerTexture.loadFromFile("images/tower.png")) {
        return 1;
    }

    // initialise enemies
    enemy *enemy1 = new enemy(enemyTexture, "enemy1", 1,2,3,4);
    enemy *enemy2 = new enemy(enemyTexture, "enemy1", 5,6,7,8);

    // initialise towers
    tower *tower1 = new AOETower(towerTexture, "tower1", 10,20);
    tower *tower2 = new rangedTower(towerTexture, "tower2", 30, 40);

    // initialise object
    gameMap map = gameMap();

    // add towers
    map.add_tower(tower1);
    map.add_tower(tower2);

    // number of towers on map
    std::cout << map.get_towers().size() << std::endl; // should be 2
    std::cout << map.get_towers()[0]->get_name() << std::endl; // should be "tower1"

    map.spawn_enemy(enemy1);
    map.spawn_enemy(enemy2);

    // get the towers to attack
    map.towers_attack();
    std::cout << map.get_enemies()[0]->get_health() << std::endl; // should be 1 since 2 towers have attacked

    // remove an enemy
    map.remove_enemy(enemy2);
    std::cout << map.get_enemies().size() << std::endl; // should be 1 since 1 enemy has been removed

    return 0;
}

// g++ gameMapTest.cpp -lsfml-system -lsfml-window -lsfml-graphics gameObject.cpp enemy.cpp tower.cpp AOETower.cpp rangedTower.cpp gameMap.cpp -o gameMapTest