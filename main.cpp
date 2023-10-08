// Standard libraries
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <cmath>

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

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Tower Defence");

    // Define the grid parameters
    int gridSize = 10;
    float cellSize = 800.0f / gridSize;

    // Create a 2D array of sprites for the grid
    std::vector<std::vector<sf::Sprite>> grid(gridSize, std::vector<sf::Sprite>(gridSize));

    // Load a texture for the grid cells (you should have an image file)
    sf::Texture groundTexture;
    if (!groundTexture.loadFromFile("images/ground.png")) {
        return 1; // Exit if the texture fails to load
    }

    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile("images/enemy.png")) {
        return 1;
    }

    sf::Texture towerTexture;
    if (!towerTexture.loadFromFile("images/tower.png")) {
        return 1;
    }

    // Set the texture for each sprite in the grid
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            grid[i][j].setTexture(groundTexture);
            grid[i][j].setScale(cellSize / groundTexture.getSize().x, cellSize / groundTexture.getSize().y);
            grid[i][j].setPosition(i * cellSize, j * cellSize);
        }
    }

    gameMap map = gameMap();
    enemy enemy3 = enemy(enemyTexture, "enemy1", 100, 100, 10, 10);
    enemy enemy2 = enemy(enemyTexture, "enemy2", 200, 200, 10, 10);
    // map.spawn_enemy(&enemy1);
    // map.spawn_enemy(&enemy2);

    // tower tower1 = tower(towerTexture, "tower1", 0,0);


    int clock = 0;

    // game loop
    while (window.isOpen()) {

        clock++;
        if (clock > 1000) {
            clock = 0;
        }

        //segfault
        if (clock == 1000) {
            map.spawn_enemy(new enemy(enemyTexture, "enemy1", rand()%(int(cellSize*gridSize)), -100, 10, 2));
        }

        if (clock%20 == 0) {
            for (int i=0; i<map.get_enemies().size(); i++) {
                map.get_enemies()[i]->moveObject(sf::Vector2f(0,map.get_enemies()[i]->get_speed()));
            }
        }

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Set the sprite position to the mouse click location
                    sf::Vector2f click_position;
                    click_position.x = (std::floor(event.mouseButton.x/80))*80;
                    click_position.y = (std::floor(event.mouseButton.y/80))*80;
                    // tower1.set_pos(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                    map.add_tower(new tower(towerTexture, "Tower1", click_position.x, click_position.y));
                    // tower1.set_pos(click_position);
                    
                }
            }
        }

        //clear the window
        window.clear(sf::Color::White);

        // Draw the grid of sprites
        for (int i = 0; i < gridSize; ++i) {
            for (int j = 0; j < gridSize; ++j) {
                window.draw(grid[i][j]);
            }
        }

        for (int i=0; i<map.get_towers().size(); i++) {
            window.draw(map.get_towers()[i]->get_object());
        }

        // window.draw(enemy1.get_object());
        for (int i=0; i<map.get_enemies().size(); i++) {
            window.draw(map.get_enemies()[i]->get_object());
        }

        // window.draw(tower1.get_object());

        window.display();

    }

    return 0;
}
