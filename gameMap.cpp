#include "gameMap.h"
#include <iostream>

// default constructor, no variables should be initialised
gameMap::gameMap() {}

// add a tower to the towers vector
void gameMap::add_tower(tower* new_tower) {

    this->towers.push_back(new_tower); 

}

// add an enemy to the enemies vector
void gameMap::spawn_enemy(enemy* new_enemy) {

    this->enemies.push_back(new_enemy);
    
}

// remove a specific enemy from enemies vector
void gameMap::remove_enemy(enemy* del_enemy) {

    this->enemies.erase(std::remove(this->enemies.begin(), this->enemies.end(), del_enemy), this->enemies.end());
    delete del_enemy; // enemies stored in dynamic memory, must be deleted or segfault

}

// get all towers to attack
void gameMap::towers_attack() {

    // call attack function for every tower
    for (int i=0; i<this->towers.size(); i++) {
        this->towers[i]->attack(this->enemies);
    }

}

// return enemies vector
std::vector < enemy* > gameMap::get_enemies() {return this->enemies;}

// return towers vector
std::vector < tower* > gameMap::get_towers() {return this->towers;}

// destructor. Game will segfault without properly removing dynamically allocated objects
gameMap::~gameMap() {
    
    // delete all enemies from enemies vector
    for (int i=0; i<this->enemies.size(); i++) {
        delete enemies[i];
    }

    // delete all towers from towers vector
    for (int i=0; i<this->towers.size(); i++) {
        delete towers[i];
    }
}
