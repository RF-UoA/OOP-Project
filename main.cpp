// Standard libraries
#include <iostream>
#include <math.h>

// SFML modules and libraries
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

// Class files


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
    float windowHeight = 1080;
    float windowWidth = 1920;

    // Create display window object
    static sf::RenderWindow window(sf::VideoMode(windowWidth,windowHeight), "Tower defense");

    sf::Texture texture;
    if (!texture.loadFromFile("images/Slime.png")) {
        cout << "Error loading texture" << endl;
        return 0;
    }

    sf::Sprite sprite; 
    sprite.setTexture(texture);

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
        
        // draw all game objects to the window
        draw_window(&window, &sprite);
        
    }

    // level number = 0
    // player money = 100

    // generate map
    // draw map
    // draw tower
    // hold game until play button is selected

    // Level loop
        // level number += 1
        // add one length to path
        // spawn enemies based on level number

        // game loop
            // move all enemies by 1 value
            // run 'attack' method on all towers (they may only attack if enemies are in range)
            // if player purchases a new tower, place tower on map
            // drawWindow function
                // re-draw map
                // re-draw towers
                // draw all enemies
                // draw all projectiles
        

    return 0;
}