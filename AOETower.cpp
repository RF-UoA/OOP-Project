#include <iostream>
#include <cmath>
#include "AOETower.h"

using namespace std;

AOETower::AOETower() : tower() {this->type = 2;}

AOETower::AOETower(sf::Texture texture, std::string name, float x, float y) : tower(texture, name, x, y) {this->type = 2; this->range = 300;}

void AOETower::attack(std::vector < enemy* > enemies) {
    
    for (int i=0; i<enemies.size(); i++) {
        sf::Vector2f enemy_position = enemies[i]->get_object().getPosition();
        sf::Vector2f offset;
        offset.x -= 40;
        offset.y -= 40;
        sf::Vector2f displacement = enemy_position - this->pos + offset;
        float distance = pow(pow(displacement.x,2)+pow(displacement.y,2),0.5);

        if (distance <= this->range) {
            enemies[i]->take_damage(1);
            this->set_attacking(250);
            // std::cout << this->name << " Successfully attacked an enemy! Enemy now has " << enemies[i]->get_health() << " health" << std::endl;
        }
    }
}