#include <iostream>

// SFML modules and libraries
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>


#include "gameObject.h"
#include "enemy.h"
#include "enemy_heavy.h"



int main(void) {

    // load texture
    sf::Texture myTexture;
    if (!myTexture.loadFromFile("images/enemy.png")) {
        return 1;
    }

    // initialise enemy
    enemy enemy1 = enemy_heavy(myTexture, "enemy1", 1,2,3,4);

    // check class member functions
    std::cout << enemy1.get_name() << std::endl;
    std::cout << enemy1.get_health() << std::endl;
    std::cout << enemy1.get_object().getPosition().x << std::endl;
    std::cout << enemy1.get_speed() << std::endl;

    // move enemy
    enemy1.moveObject(sf::Vector2f(10,10));

    return 0;
}

// g++ heavyEnemyTest.cpp -lsfml-system -lsfml-window -lsfml-graphics gameObject.cpp enemy.cpp enemy_heavy.cpp -o heavyEnemyTest