#include <iostream>

// SFML modules and libraries
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>


#include "gameObject.h"
#include "enemy.h"



int main(void) {

    sf::Texture myTexture;
    if (!myTexture.loadFromFile("images/enemy.png")) {
        return 1;
    }
    enemy enemy1 = enemy(myTexture, "enemy1", 1,2,3,4);
    std::cout << enemy1.get_name() << std::endl;
    std::cout << enemy1.get_health() << std::endl;
    std::cout << enemy1.get_object().getPosition().x << std::endl;
    std::cout << enemy1.get_speed() << std::endl;

    enemy1.moveObject(sf::Vector2f(10,10));

    return 0;
}

// g++ enemyTest.cpp -lsfml-system -lsfml-window -lsfml-graphics gameObject.cpp enemy.cpp -o enemyTest