// Standard libraries
#include <iostream>
#include <math.h>

// SFML modules and libraries
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

// Class files
#include "gameObject.h"
#include "gameMap.h"
#include "tower.h"
#include "enemy.h"
#include "tile.h"

using namespace std;

// Draw to window function
void draw_window(sf::RenderWindow* window, sf::Sprite* sprite) {

    window->clear();


    window->draw(*sprite);
    window->display();

}

// main function
int main(void) {

    // variables for display window size
    float windowHeight = 1000;
    float windowWidth = 1000;

    // Create display window object
    static sf::RenderWindow window(sf::VideoMode(windowWidth,windowHeight), "Tower defense");

    sf::Texture texture;
    if (!texture.loadFromFile("images/Slime.png")) {
        cout << "Error loading texture" << endl;
        return 0;
    }



    sf::Sprite sprite; 
    sprite.setTexture(texture);

    gameMap map = gameMap();

    // main game loop
    while (window.isOpen()) {

        // create event object
        sf::Event event;

        // check if window is closed
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            sprite.move(sf::Vector2f(0.1, 0.1));
        }

        window.clear();

        for (int i=0; i<2; i++) {
            for (int j=0; j<2; j++) {
                window.draw(map.tiles[i][j]->sprite);
            }
        }


        // window.draw(*sprite);
        window.display();
        
        // draw all game objects to the window
        // draw_window(&window, &sprite, map);
        
    }

    // level number = 0
    // player money = 100

    // generate gameMap
    // draw gameMap
    // draw tower
    // hold game until play button is selected

    // Level loop
        // level number += 1
        // add one length to path
        // spawn enemies based on level number

        // game loop
            // move all enemies by 1 value
            // run 'attack' method on all towers (they may only attack if enemies are in range)
            // if player purchases a new tower, place tower on gameMap
            // drawWindow function
                // re-draw gameMap
                // re-draw towers
                // draw all enemies
                // draw all projectiles
        

    return 0;
}