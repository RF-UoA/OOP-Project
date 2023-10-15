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
#include "rangedTower.h"
#include "AOETower.h"
#include "enemy.h"
#include "tile.h"
#include "enemy_light.h"
#include "enemy_medium.h"
#include "enemy_heavy.h"

using namespace std;

int main() {

    // Defining the game window
    sf::RenderWindow window(sf::VideoMode(800, 800), "Tower Defence");
    window.setFramerateLimit(120);

    // Define the grid parameters
    int gridSize = 10;
    float cellSize = 800.0f / gridSize;

    // Define pause menu position and state
    int pause_pos = 800/2.6 - 800/10;
    bool pause = 0;

    // Define toggle inputs
    bool lock_input = false;
    bool last_input_1 = true;
    bool menu_toggle = true;
    bool game_over = false;

    // Create tower selection Sprites
    sf::Texture towerTexture1;
    if (!towerTexture1.loadFromFile("images/Tower_1.png")) {
        return 1;
    }
    const sf::Texture *towerPointer1 = &towerTexture1;

    sf::Texture towerTexture2;
    if (!towerTexture2.loadFromFile("images/Tower_2.png")) {
        return 1;
    }
    const sf::Texture *towerPointer2 = &towerTexture2;

    // Create single box for both tower selections
    sf::RectangleShape towerUI(sf::Vector2f(180, 70));    
    towerUI.setFillColor(sf::Color::White);
    towerUI.setPosition(0,730);

    //Create pause menu and main menu assets
        // main menu
        sf::Texture menuTexture;
        if (!menuTexture.loadFromFile("images/Menu.png")) {
            return 1;
        }
        const sf::Texture *menuPointer = &menuTexture;
        sf::RectangleShape menu(sf::Vector2f(800, 800));
        menu.setFillColor(sf::Color::White);
        menu.setPosition(0,0);
        menu.setTexture(menuPointer);

        //Transparent Backdrop
        sf::RectangleShape transparent(sf::Vector2f(800, 800));
        transparent.setFillColor(sf::Color(0,0,0,128));
        transparent.setPosition(0,0);

        // Load texture for pause menu
        sf::Texture pauseTexture;
        if (!pauseTexture.loadFromFile("images/Pause.jpg")) {
            return 1;
        }
        // create a pointer to the texture
        const sf::Texture *pausePointer = &pauseTexture;
        // make the pause menu shape
        sf::RectangleShape backdrop(sf::Vector2f(800/2.6, 800/2));
        backdrop.setFillColor(sf::Color::White);
        backdrop.setPosition((800/2) - (800/2.6)/2, 800/4);
        // access texture pointer annd apply it to the shape
        backdrop.setTexture(pausePointer);

    // Create a 2D array of sprites for the grid
    std::vector<std::vector<sf::Sprite>> grid(gridSize, std::vector<sf::Sprite>(gridSize));

    // Load a texture for the grid cells (you should have an image file)
    sf::Texture groundTexture;
    if (!groundTexture.loadFromFile("images/ground.png")) {
        return 1; // Exit if the texture fails to load
    }

    // Load texture for main enemies
    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile("images/enemy.png")) {
        return 1;
    }

    // Load texture for sub-class enemies
    sf::Texture enemyLight;
    if (!enemyLight.loadFromFile("images/enemyLight.png")) {
        return 1;
    }
    sf::Texture enemyMedium;
    if (!enemyMedium.loadFromFile("images/enemyMedium.png")) {
        return 1;
    }
    sf::Texture enemyHeavy;
    if (!enemyHeavy.loadFromFile("images/enemyHeavy.png")) {
        return 1;
    }
    // Load texture for towers
    sf::Texture towerTexture;
    if (!towerTexture.loadFromFile("images/tower.png")) {
        return 1;
    }
    sf::Texture towerTextureRange;
    if (!towerTextureRange.loadFromFile("images/towerRanged.png")) {
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

    // used to draw lines to the enemies when attacking
    sf::Vector2f firstEnemyPosition;
    firstEnemyPosition.x = 0;
    firstEnemyPosition.y = 0;

    // Initialise the game map
    gameMap map = gameMap();

    // Change this to determine which tower or enemy is placed
    int towerSelection = 1;
    int enemySelect;

    // Currency
    int playerMoney = 200;
    
    // Make an integer value into a string and convert to "Text" for visual display
    // load font from file and apply it to the current currency count
    sf::Font font;
    font.loadFromFile("font/OpenSans-Bold.ttf");
    string moneyDisplay = to_string(playerMoney);
    sf::Text visibleMoney;
    visibleMoney.setFont(font);
    visibleMoney.setString("$" + moneyDisplay);
    visibleMoney.setCharacterSize(50);
    visibleMoney.setFillColor(sf::Color::White);
    visibleMoney.setStyle(sf::Text::Bold);
    visibleMoney.setPosition(10,0);

    sf::Text menuTitle;
    menuTitle.setCharacterSize(70);
    menuTitle.setFont(font);
    menuTitle.setString("Tower Defence");
    menuTitle.setFillColor(sf::Color::Black);
    menuTitle.setPosition(130,100);

    sf::Text menuMessage;
    menuMessage.setCharacterSize(20);
    menuMessage.setFont(font);
    menuMessage.setString("\
    Welcome to tower defence! In this minigame enemies\n\
    will run down the map to try and breach your\n\
    defences. Place defensive towers at strategic\n\
    locations to defend your land! There are two types\n\
    of tower, ranged and area attack. Press 1 and 2 on\n\
    your keyboard to switch between the types.Each enemy\n\
    kill will give you money which you can use to build\n\
    more towers. Select a location on the grid to build\n\
    a tower of your choice. Good luck!\n\n\
    click to begin.");
    menuMessage.setFillColor(sf::Color::Black);
    menuMessage.setPosition(110,200);

    sf::Text errorMessage;
    errorMessage.setCharacterSize(30);
    errorMessage.setFont(font);
    errorMessage.setString("Square already occupied!");
    errorMessage.setFillColor(sf::Color::White);
    errorMessage.setPosition(200,380);
    int errorMessageCountdown = 0;
    int errorText;

    // Initialise the game clock
    int clock = 0;

    // opening menu
    bool startGame = true;

    // game loop
    while (window.isOpen()) {

        // Draw the starting menu
        while (startGame == true) {

            window.clear();
            for (int i = 0; i < gridSize; ++i) {
                for (int j = 0; j < gridSize; ++j) {
                    window.draw(grid[i][j]);
                }
            }
            window.draw(menuTitle);
            window.draw(menuMessage);
            window.display();


            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close(); 
                    return 0;
                } else if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        startGame = false;
                    }
                }
            } 
        }       

        // Manual game clock, increases every frame
        clock++;
        if (clock > 1000) {
            clock = 1;
        }

        // Periodic spawning of enemies
        if (clock == 1000) {
            // randomise seed for aw value between 0 and 10
            srand(time(NULL));
            enemySelect = (rand() % 11) - 1;
            enemySelect = 6;

            if (enemySelect <= 2) {
                map.spawn_enemy(new enemy_light(enemyLight, "enemy1", rand()%(int(cellSize*gridSize)), -100, 10, 2.f));
                //cout << "Light" << endl;
            } else if (enemySelect >= 8) {
                map.spawn_enemy(new enemy_heavy(enemyHeavy, "enemy1", rand()%(int(cellSize*gridSize)), -100, 10, 2.f));
                //cout << "Heavy" << endl;
            } else {
                map.spawn_enemy(new enemy(enemyMedium, "enemy1", rand()%(int(cellSize*gridSize)), -100, 10, 2.f));
                map.spawn_enemy(new enemy_heavy(enemyHeavy, "enemy1", rand()%(int(cellSize*gridSize)), -100, 10, 2.f));
                //cout << "Medium" << endl;
            }
        }

        // Enemy movement handling
        if (clock%5 == 0) {
            for (int i=0; i<map.get_enemies().size(); i++) {
                map.get_enemies()[i]->moveObject(sf::Vector2f(0,map.get_enemies()[i]->get_speed()));
            }
        }

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();    

            // Query for mouse click    
            } else if (event.type == sf::Event::MouseButtonPressed) {
                
                if (event.mouseButton.button == sf::Mouse::Left) {
                    
                    // Set the sprite position to the mouse click location
                    sf::Vector2f click_position;
                    click_position.x = (std::floor(event.mouseButton.x/80))*80;
                    click_position.y = (std::floor(event.mouseButton.y/80))*80;
                    
                    // logic to check if square is already occupied
                    bool empty_square = true;
                    for (int i=0; i<map.get_towers().size(); i++) {
                        if (map.get_towers()[i]->get_pos() == click_position) {
                            empty_square = false;
                        }
                    }

                    // If square is not occupied, place the tower
                    if (empty_square == true) {
                        if (towerSelection == 1 && playerMoney >= 100) {
                            map.add_tower(new rangedTower(towerTextureRange, "Tower1", click_position.x, click_position.y));
                            playerMoney -= 100;
                        } else if (towerSelection == 2 && playerMoney >= 150) {
                            map.add_tower(new AOETower(towerTexture, "Tower1", click_position.x, click_position.y));
                            playerMoney -= 150;
                        }
                    } else {
                        if (map.get_enemies().size() > 0) {
                            firstEnemyPosition = map.get_enemies()[0]->get_object().getPosition();
                        }
                        map.towers_attack();
                        srand(time(NULL));
                        errorText = rand() % 10;
                        errorMessageCountdown = 200;
                    }                 
                }
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
                towerSelection = 1;
                last_input_1 = true;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
                towerSelection = 2;
                last_input_1 = false;
            }
        }

        // Clear the window
        window.clear(sf::Color::White);

        // Draw the ground grid
        for (int i = 0; i < gridSize; ++i) {
            for (int j = 0; j < gridSize; ++j) {
                window.draw(grid[i][j]);
            }
        }

        // draw money
        window.draw(visibleMoney);
        //window.draw(visibleScore);

        // draw tower selection
        if (last_input_1 == true) {
            towerUI.setTexture(towerPointer1);
            window.draw(towerUI);
        } else if (last_input_1 == false) {
            towerUI.setTexture(towerPointer2);
            window.draw(towerUI);
        }

        // delete dead enemies
        bool gameOver = false;
        for (int i=0; i<map.get_enemies().size(); i++) {
            if (map.get_enemies()[i]->get_object().getPosition().y > 800) {
                map.remove_enemy(map.get_enemies()[i]);
                game_over = true;

            } else if (map.get_enemies()[i]->get_health() <= 0) {
                playerMoney += 100;
                map.remove_enemy(map.get_enemies()[i]);
                // cout << "$" << playerMoney << endl;
                playerMoney += 100;
            }
        }

        // update money
        moneyDisplay = to_string(playerMoney);
        visibleMoney.setString("$" + moneyDisplay);
        
        // handle game ending
        while (game_over == true) {
            menuTitle.setString("Game Over!");
            menuTitle.setPosition(180,250);
            for (int i = 0; i < gridSize; ++i) {
                for (int j = 0; j < gridSize; ++j) {
                    window.draw(grid[i][j]);
                }
            }
            window.draw(menuTitle);
            window.display();
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();   
                    return 0;   
                } else if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        window.close();   
                        return 0;
                    }
                }
            }
        }
        
        // Attack enemies periodically
        if (clock%250 == 0) {
            if (map.get_enemies().size() > 0) {
                firstEnemyPosition = map.get_enemies()[0]->get_object().getPosition();
            }
            map.towers_attack();
        }

        // Draw the attacks
        for (int i=0; i<map.get_towers().size(); i++) {
            
            // Tower must be of AOE type AND actively attacking
            if (map.get_towers()[i]->get_type() == 2 && map.get_towers()[i]->get_attacking() > 0) {
                
                // Draw a circle for the attack range
                sf::CircleShape circle(map.get_towers()[i]->get_range());
                sf::Vector2f currentTowerPos = map.get_towers()[i]->get_object().getPosition();
                currentTowerPos.x -= (circle.getRadius() - 40);
                currentTowerPos.y -= (circle.getRadius() - 40);
                circle.setFillColor(sf::Color(250, 100, 50, 0.5 * map.get_towers()[i]->get_attacking()));
                circle.setPosition(currentTowerPos);
                window.draw(circle);

            // Tower must be of ranged type AND actively attacking    
            } else if (map.get_towers()[i]->get_type() == 1 && map.get_towers()[i]->get_attacking() > 0) {
                if (map.get_enemies().size() > 0 || firstEnemyPosition.x > 0) {
                    sf::Vertex line[] = {
                    sf::Vertex(map.get_towers()[i]->get_object().getPosition() + sf::Vector2f(40,40), sf::Color(0, 0, 250, map.get_towers()[i]->get_attacking())),
                    sf::Vertex(firstEnemyPosition + sf::Vector2f(20,20), sf::Color(0, 0, 250, map.get_towers()[i]->get_attacking())),
                    };
                    window.draw(line, 2, sf::Lines);
                }
            }

            // Stop 'attacking' from reaching far below 0 (safety feature)
            if (map.get_towers()[i]->get_attacking() < 0) {
                map.get_towers()[i]->set_attacking(0);

            // Decrease attacking (corresponds to the number of frames the attack is visible for)    
            } else {
                map.get_towers()[i]->set_attacking(map.get_towers()[i]->get_attacking()-1);
            }

        }

        // Draw the towers
        for (int i=0; i<map.get_towers().size(); i++) {
            window.draw(map.get_towers()[i]->get_object());
        }

        // Draw the enemies
        for (int i=0; i<map.get_enemies().size(); i++) {
            if (!map.get_enemies()[i]->get_health() <= 0) {
                window.draw(map.get_enemies()[i]->get_object());
            }
        }

        // draw the error message
        if (errorMessageCountdown > 0) {
            switch (errorText) {
                case 1: 
                    errorMessage.setString("FIRE!");
                    break;
                case 2:
                    errorMessage.setString("THERES TOO MANY OF THEM!");
                    break;
                case 3:
                    errorMessage.setString("THEY DONT STAND A CHANCE!");
                    break;
                case 4:
                    errorMessage.setString("DEFEND THE CASTLE!");
                    break;
                case 5:
                    errorMessage.setString("I'm tired");
                    break;
                case 6:
                    errorMessage.setString("HELP!");
                    break;
                case 7:
                    errorMessage.setString("WHY AM I DOING ALL THE WORK?!");
                    break;
                case 8:
                    errorMessage.setString("KILL THEM!");
                    break;
                case 9:
                    errorMessage.setString("Slime You Later!");
                    break;
                case 10:
                    errorMessage.setString("BRATATATATAT");
                    break;
                default:
                    break;
            }
            errorMessage.setFillColor(sf::Color(250,250,250,errorMessageCountdown+50));
            window.draw(errorMessage);
            errorMessageCountdown--;
        }
    
        // Update the window
        window.display();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && (pause == false)) {
                //std::cout << "Paused" << std::endl;
                // draw objects to the window
                window.draw(transparent);
                window.draw(backdrop);
                //window.draw(resume);
                window.display();
                // pause the game
                pause = true;
                lock_input = true;
        }
        
        while (pause == true) {
            // Poll for events, resets inputs so they aren't retroactively registered
            while (window.pollEvent(event)) {}
            // lock the input to prevent multiple clicks
            while (lock_input == true) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) == false && lock_input == true) {
                    //cout << "1" << endl;
                    lock_input = false;
                }
            }

            // Close the window if close button is clicked
            if (event.type == sf::Event::Closed) {
                window.close();   
                return 0; 
            }

            // If the user presses escape
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && (pause == true)) {
                // lock the input until they release escape
                lock_input = true;
                while (lock_input == true) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) == false && lock_input == true) {
                    // unlock input
                    lock_input = false;
                    }
                }
                    // std::cout << "UnPaused" << std::endl;
                    // Set pause to false
                    pause = false;
            }

            // check if user presses a menu button and output accordingly
            sf::Vector2i menu_click_position = sf::Mouse::getPosition(window);
            // cout << menu_click_position.x << "    ";
            // cout << menu_click_position.y << endl;
            if(event.type == sf::Event::MouseButtonPressed) {
                if (menu_click_position.x >= 282 && menu_click_position.x <= 517) {
                    if (menu_click_position.y >= 245 && menu_click_position.y <= 333) {
                        pause = false;
                    } else if (menu_click_position.y >= 345 && menu_click_position.y <= 433) {
                        // SAVE THE SCORE AND TELL THE PLAYER
                        //cout << "Save" << endl;
                    } else if (menu_click_position.y >= 445 && menu_click_position.y <= 533) {
                        //cout << "close" << endl;
                        window.close();   
                        return 0; 
                    }
                }
            }
        }
    }

    return 0;
}