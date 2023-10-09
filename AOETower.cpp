#include <iostream>
#include <cmath>
#include "AOETower.h"

AOETower::AOETower() : tower() {}

AOETower::AOETower(sf::Texture texture, std::string name, float x, float y) : tower(texture, name, x, y) {}

void AOETower::attack(std::vector < enemy* > enemies) {
    
    for (int i=0; i<enemies.size(); i++) {
        sf::Vector2f enemy_position = enemies[i]->get_object().getPosition();
        sf::Vector2f displacement = enemy_position - this->pos;
        float distance = pow(pow(displacement.x,2)+pow(displacement.y,2),0.5);

        float range = 300;

        if (distance <= range) {
            enemies[i]->take_damage(1);
            std::cout << this->name << " Successfully attacked an enemy! Enemy now has " << enemies[i]->get_health() << " health" << std::endl;
        }
    }
}