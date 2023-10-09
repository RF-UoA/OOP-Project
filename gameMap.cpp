#include "gameMap.h"
#include <iostream>

gameMap::gameMap() {}

void gameMap::add_tower(tower* new_tower) {

    this->towers.push_back(new_tower); 

}

void gameMap::spawn_enemy(enemy* new_enemy) {

    this->enemies.push_back(new_enemy);
    
}

void gameMap::remove_enemy(enemy* del_enemy) {

    this->enemies.erase(std::remove(this->enemies.begin(), this->enemies.end(), del_enemy), this->enemies.end());

}

void gameMap::towers_attack() {

    // call attack function for every tower
    for (int i=0; i<this->towers.size(); i++) {
        this->towers[i]->attack(this->enemies);
    }

}

void gameMap::move_enemies() {

}

std::vector < enemy* > gameMap::get_enemies() {return this->enemies;}

std::vector < tower* > gameMap::get_towers() {return this->towers;}

gameMap::~gameMap() {
    
    for (int i=0; i<this->enemies.size(); i++) {
        delete enemies[i];
    }

    for (int i=0; i<this->towers.size(); i++) {
        delete towers[i];
    }
}
