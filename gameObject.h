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
        int x_pos;
        int y_pos;
        sf::Texture texture;
        std::string name;
        sf::Sprite* object;

    public:
        gameObject();
        gameObject(sf::Texture texture, std::string name);
        float get_x();
        float get_y();
        void set_texture(sf::Texture texture);
        void set_name(std::string name);
        std::string get_name();
        sf::Sprite* get_object();

};

#endif