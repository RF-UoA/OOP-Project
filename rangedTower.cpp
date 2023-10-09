#include <iostream>
#include <cmath>
#include "rangedTower.h"

rangedTower::rangedTower() : tower() {this->type = 1;}

rangedTower::rangedTower(sf::Texture texture, std::string name, float x, float y) : tower(texture, name, x, y) {this->type = 1;}

void rangedTower::attack(std::vector < enemy* > enemies) {

    // Attacks the closest enemy
    if (enemies.size() > 0) {
        enemies[0]->take_damage(1);
        this->set_attacking(250);
        // std::cout << this->name << " Successfully attacked an enemy! Enemy now has " << enemies[0]->get_health() << " health" << std::endl;
    }
}
