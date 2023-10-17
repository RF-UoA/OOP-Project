#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

// General libraries
#include <string>

// SFML modules and libraries
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class gameObject {
    protected:
        sf::Vector2f pos; // coordinate position
        sf::Texture texture; // object's texture
        std::string name; // object's name
        sf::Sprite object; // object's sprite

    public:
        gameObject(); // default constructor
        gameObject(sf::Texture texture, std::string name, float x, float y); // regular constructor
        sf::Vector2f get_pos(); // get the position of the sprite
        void set_pos(sf::Vector2f pos); // set the position of the sprite
        void set_texture(sf::Texture texture); // set the texture of the object
        void set_name(std::string name); // set the name of the object
        std::string get_name(); // get the name of the object
        sf::Sprite get_object(); // get the sprite for the object
        void moveObject(sf::Vector2f movement); // move the object's sprite

};

#endif