#include "gameMap.h"
#include <iostream>

gameMap::gameMap() {

    // initialise all values and arrays to default values
    // games will always start with empty arrays which will grow
    this->total_num = 0;
    this->num_towers = 0;
    this->num_enemies = 0;
    this->num_tiles = 0;
    // this->all_objects = new gameObject*[total_num];
    // this->enemies = new enemy*[1000];
    // this->towers = new tower*[num_towers];
}

void gameMap::add_tower(tower* new_tower) {
    
    // create a temporary array that is 1 unit longer than towers array
    tower** temp = new tower*[this->num_towers+1];

    // copy contents of old tower array to temp
    for (int i=0; i<this->num_towers-1; i++) {
        temp[i] = this->towers[i];
    }

    // copy new tower to temp
    temp[this->num_towers] = new_tower;
    this->num_towers++;

    // remove old tower array and re-allocate
    delete [] this->towers;
    this->towers = new tower*[this->num_towers];

    // copy temp array to new tower array
    for (int i=0; i<this->num_towers-1; i++) {
        this->towers[i] = temp[i];
    }

    // delete temp array
    delete [] temp;

}

void gameMap::spawn_enemy(enemy* new_enemy) {

    // this->enemies[this->num_enemies] = new_enemy;
    // this->num_enemies++;

    std::cout << "enemy spawned!" << std::endl;
    this->enemies.push_back(new_enemy);

    // for (int i=0; i<this->enemies.size(); i++) {
    //     std::cout << enemies[i]->get_name() << std::endl;
    // }
    
}

void gameMap::remove_enemy(enemy* del_enemy) {

    this->enemies.erase(std::remove(this->enemies.begin(), this->enemies.end(), del_enemy), this->enemies.end());

}

void gameMap::towers_attack() {

    // call attack function for every tower
    // for (int i=0; i<this->num_towers; i++) {
    //     this->towers[i]->attack(this->enemies, this->num_enemies);
    // }

}

void gameMap::move_enemies() {

}

int gameMap::get_num_enemies() {return this->num_enemies;}

std::vector < enemy* > gameMap::get_enemies() {return this->enemies;}

gameMap::~gameMap() {
    
    for (int i=0; i<this->enemies.size(); i++) {
        delete enemies[i];
    }
}
