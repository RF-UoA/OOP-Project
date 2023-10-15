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
    enemy enemy1 = enemy(myTexture, "enemy1", 1,1,1,1);
    std::cout << enemy1.get_name() << std::endl;
    return 0;
}