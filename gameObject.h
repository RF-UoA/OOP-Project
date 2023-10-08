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
        sf::Vector2f pos;
        sf::Texture texture;
        std::string name;
        sf::Sprite object;

    public:
        gameObject();
        gameObject(sf::Texture texture, std::string name, float x, float y);
        sf::Vector2f get_pos();
        void set_pos(sf::Vector2f pos);
        void set_texture(sf::Texture texture);
        void set_name(std::string name);
        std::string get_name();
        sf::Sprite get_object();
        void moveObject(sf::Vector2f movement);

};

#endif