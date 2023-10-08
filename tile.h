#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include "gameObject.h"

// class tile : public gameObject {
//     protected:
//         bool path;
//     public:
//         tile();
//         tile(sf::Texture texture, std::string name, float x, float y, bool path);
// };

class tile {
    public:
        bool isPassable;
        bool isExit;
        sf::Vector2f pos;
        sf::Texture texture;
        sf::Sprite sprite;
        tile(std::string, float, float, bool, bool);
        bool setUpSprite(std::string);

};

#endif