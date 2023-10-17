#include <iostream>
#include <cmath>
#include "AOETower.h"

using namespace std;

// default constructor
AOETower::AOETower() : tower() {this->type = 2;}

// regular constructor
AOETower::AOETower(sf::Texture texture, std::string name, float x, float y) : tower(texture, name, x, y) {this->type = 2; this->range = 300;}

// attack enemies
void AOETower::attack(std::vector < enemy* > enemies) {
    
    // check if any enemy is in range
    for (int i=0; i<enemies.size(); i++) {
        sf::Vector2f enemy_position = enemies[i]->get_object().getPosition();
        sf::Vector2f offset;
        offset.x -= 40;
        offset.y -= 40;
        sf::Vector2f displacement = enemy_position - this->pos + offset;
        float distance = pow(pow(displacement.x,2)+pow(displacement.y,2),0.5);

        if (distance <= this->range) { // if an enemy is in range, attack
            enemies[i]->take_damage(1);
            this->set_attacking(250); // update attacking period
        }
    }
}