#include <iostream>

// SFML modules and libraries
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "gameObject.h"



int main(void) {

    sf::Texture myTexture;
    if (!myTexture.loadFromFile("images/enemy.png")) {
        return 1;
    }

    // testing gameObject member function
    gameObject object1 = gameObject(myTexture, "object1", 1,2);
    std::cout << object1.get_name() << std::endl;
    std::cout << object1.get_pos().x << std::endl;
    std::cout << object1.get_object().getPosition().x << std::endl;
    
    // using functions to modify attributes
    object1.set_name("new object");
    object1.set_texture(myTexture);
    object1.moveObject(sf::Vector2f(10,20));

    // testing result
    std::cout << object1.get_name() << std::endl;
    std::cout << object1.get_pos().x << std::endl;
    std::cout << object1.get_pos().y << std::endl;

    return 0;
}

// g++ gameObjectTest.cpp -lsfml-system -lsfml-window -lsfml-graphics gameObject.cpp -o gameObjectTest