#include "map.h"
#include <iostream>

map::map() {

    // initialise all values and arrays to default values
    // games will always start with empty arrays which will grow
    this->total_num = 0;
    this->num_towers = 0;
    this->num_enemies = 0;
    this->num_paths = 0;
    this->all_objects = new gameObject*[total_num];
    this->enemies = new enemy*[num_enemies];
    this->towers = new tower*[num_towers];
    this->paths = new gameObject*[num_paths];

}

void map::add_tower(tower* new_tower) {
    
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

void map::spawn_enemy(enemy* new_enemy) {
    
    // create a temporary array that is 1 unit longer than enemies array
    enemy** temp = new enemy*[this->num_enemies+1];

    // copy contents of old enemies array to temp
    for (int i=0; i<this->num_enemies-1; i++) {
        temp[i] = this->enemies[i];
    }

    // copy new enemy to temp
    temp[this->num_enemies] = new_enemy;
    this->num_enemies++;

    // remove old enemies array and re-allocate
    delete [] this->enemies;
    this->enemies = new enemy*[this->num_enemies];

    // copy temp array to new enemies array
    for (int i=0; i<this->num_enemies-1; i++) {
        this->enemies[i] = temp[i];
    }

    // delete temp array
    delete [] temp;
}

void map::remove_enemy(enemy* del_enemy) {

    // create new temporary array and reduce total num of enemies
    enemy** temp = new enemy*[this->num_enemies-1];
    this->num_enemies--;

    // search for deleted enemy and skip array copy when found
    int skipped_index = 0;
    for (int i=0; i<this->num_enemies; i++) {
        if (this->enemies[i] == del_enemy) {
            skipped_index = 1;
            std::cout << "successfully found and skipped an enemy" << std::endl;
        }
        temp[i] = this->enemies[i+skipped_index]; 
    }

}

void map::towers_attack() {

    // call attack function for every tower
    for (int i=0; i<this->num_towers; i++) {
        this->towers[i]->attack(this->enemies, this->num_enemies);
    }

}

void map::generate_path() {

}

void map::move_enemies() {

}
