// Standard libraries
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <string>
#include <string.h>

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
#include "enemy_light.h"
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

    // define clock interval for speed up and slow down
    int clockInterval = 1000;  
    int attackPeriod = 250;
    int movePeriod = 4;

    // Create tower selection Sprites
    sf::Texture towerTexture1;
    if (!towerTexture1.loadFromFile("images/Tower_1.png")) {
        return 1;
    }
    const sf::Texture *towerPointer1 = &towerTexture1; // tower 1 selected

    sf::Texture towerTexture2;
    if (!towerTexture2.loadFromFile("images/Tower_2.png")) {
        return 1;
    }
    const sf::Texture *towerPointer2 = &towerTexture2; // tower 2 selected

    // Create single box for both tower selections
    sf::RectangleShape towerUI(sf::Vector2f(180, 70));    
    towerUI.setFillColor(sf::Color::White);
    towerUI.setPosition(0,730);

    //Create pause menu and main menu assets
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

    // Speed up visualisation
    sf::Texture forwardTexture;
    if (!forwardTexture.loadFromFile("images/fastForward.png")) {
        return 1;
    }
    const sf::Texture *forwardPointer = &forwardTexture;
    sf::RectangleShape fastForward(sf::Vector2f(80, 80));
    fastForward.setFillColor(sf::Color::White);
    fastForward.setPosition(710,0);
    fastForward.setTexture(forwardPointer);

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

    // Load texture for light enemies
    sf::Texture enemyLight;
    if (!enemyLight.loadFromFile("images/enemyLight.png")) {
        return 1;
    }

    // Load texture for regular enemies
    sf::Texture enemyMedium;
    if (!enemyMedium.loadFromFile("images/enemyMedium.png")) {
        return 1;
    }

    // Load texture for heavy enemies
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

    // initialise enemy variable, used to draw lines to the enemies when attacking
    sf::Vector2f firstEnemyPosition;
    firstEnemyPosition.x = 0;
    firstEnemyPosition.y = 0;

    // Initialise the game map
    gameMap map = gameMap();

    // Change this to determine which tower or enemy is placed
    int towerSelection = 1;
    int enemySelect;

    // Score
    int score = 0;
    int highscore = 0;

    // Currency variable
    int playerMoney = 200;

    // reading save file
    fstream scoreFile;
    fstream highscoreFile;
    highscoreFile.open("text/highscoreStorage.txt", ios::in); // read
    if (highscoreFile.is_open()) { // if the file is open
        string readHighscore;
        while (getline(highscoreFile, readHighscore)) {
            highscore = stoi(readHighscore); // set the highscore from file
        }
        highscoreFile.close();
    }
    
    // Define a font object from file
    sf::Font font;
    font.loadFromFile("font/OpenSans-Bold.ttf");

    // Money display
    string moneyDisplay = to_string(playerMoney);
    sf::Text visibleMoney;
    visibleMoney.setFont(font);
    visibleMoney.setString("$" + moneyDisplay);
    visibleMoney.setCharacterSize(50);
    visibleMoney.setFillColor(sf::Color::White);
    visibleMoney.setStyle(sf::Text::Bold);
    visibleMoney.setPosition(10,50);

    // Score Display
    string scoreDisplay = to_string(score);
    sf::Text visibleScore;
    visibleScore.setFont(font);
    visibleScore.setString("Score: " + scoreDisplay);
    visibleScore.setCharacterSize(50);
    visibleScore.setFillColor(sf::Color::White);
    visibleScore.setStyle(sf::Text::Bold);
    visibleScore.setPosition(10,0);

    // Highscore Display
    string highscoreDisplay = to_string(highscore);
    sf::Text visibleHighscore;
    visibleHighscore.setFont(font);
    visibleHighscore.setString("Highscore: " + highscoreDisplay);
    visibleHighscore.setCharacterSize(25);
    visibleHighscore.setFillColor(sf::Color::Black);
    visibleHighscore.setStyle(sf::Text::Bold);
    visibleHighscore.setPosition(625 - (12.5 * highscoreDisplay.length()),750);

    // Visible costs
    string rangeCost = to_string(100);
    string aoeCost = to_string(150);
    sf::Text towerCosts;
    towerCosts.setFont(font);
    towerCosts.setString(rangeCost + "     " + aoeCost);
    towerCosts.setCharacterSize(25);
    towerCosts.setFillColor(sf::Color::Black);
    towerCosts.setStyle(sf::Text::Bold);
    towerCosts.setPosition(20,700);

    // Menu title display
    sf::Text menuTitle;
    menuTitle.setCharacterSize(70);
    menuTitle.setFont(font);
    menuTitle.setString("Tower Defence");
    menuTitle.setFillColor(sf::Color::Black);
    menuTitle.setPosition(130,100);

    // Menu message display
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
    a tower of your choice. Good luck!\n\
    To fast forward, hold F.\n\n\
    click to begin.\n\
    press L to load game");
    menuMessage.setFillColor(sf::Color::Black);
    menuMessage.setPosition(110,200);

    // Error message display
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

    // opening menu variable
    bool startGame = true;

    // game loop
    while (window.isOpen()) {

        // Draw the starting menu
        while (startGame == true) {

            // Clear the screen
            window.clear();

            // Draw the background grid
            for (int i = 0; i < gridSize; ++i) {
                for (int j = 0; j < gridSize; ++j) {
                    window.draw(grid[i][j]);
                }
            }

            // Draw the menu
            window.draw(menuTitle);
            window.draw(menuMessage);
            window.display();

            // check for game events
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close(); // end the program if window is closed
                    return 0;
                } else if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        startGame = false; // start the game if the mouse is clicked
                    }
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
                    scoreFile.open("text/saveStorage.txt", ios::in); // read
                    if (scoreFile.is_open()) { // if the file is open
                        string readScore;
                        while (getline(scoreFile, readScore)) {
                            score = stoi(readScore); // string to integer
                            playerMoney = stoi(readScore) + 200; // give all money back to the player
                        }
                        scoreFile.close();
                    }
                    startGame = false;
                }
            } 
        }

        // Speed up the game if 'F' is pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
            clockInterval = 500;
            attackPeriod = 125;
            movePeriod = 2;
        } else {
            clockInterval = 1000;
            attackPeriod = 250;
            movePeriod = 4;
        }
        
        // Manual game clock, increases every frame used for game events
        clock++;
        if (clock > clockInterval) {
            clock = 1;
        }
        
        // Periodic spawning of enemies
        if (clock == clockInterval) {
            // randomise seed for aw value between 0 and 10
            srand(time(NULL));
            enemySelect = (rand() % 11) - 1; // RNG for enemy spawning

            if (enemySelect <= 2) { // spawn a light enemy
                map.spawn_enemy(new enemy_light(enemyLight, "enemy1", rand()%(int(cellSize*gridSize)), -100, 10 + 0.1 * score, 2.f));
            } else if (enemySelect >= 8) { // spawn a heavy enemy
                map.spawn_enemy(new enemy_heavy(enemyHeavy, "enemy1", rand()%(int(cellSize*gridSize)), -100, 10 + 0.1 * score, 2.f));
            } else { // spawn a regular enemy
                map.spawn_enemy(new enemy(enemyMedium, "enemy1", rand()%(int(cellSize*gridSize)), -100, 10 + 0.1 * score, 2.f));
            }
        }

        // Enemy movement handling
        if (clock % movePeriod == 0) {
            for (int i=0; i<map.get_enemies().size(); i++) {
                map.get_enemies()[i]->moveObject(sf::Vector2f(0,map.get_enemies()[i]->get_speed()));
            }
        }

        sf::Event event; // variable for SFML events such as keypresses
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close(); // end program if window is closed   

            // Query for mouse click to place towers   
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
                        if (towerSelection == 1 && playerMoney >= 100) { // place a ranged tower
                            map.add_tower(new rangedTower(towerTextureRange, "Ranged Tower", click_position.x, click_position.y));
                            playerMoney -= 100; // decrease money
                        } else if (towerSelection == 2 && playerMoney >= 150) { // place an AOE tower
                            map.add_tower(new AOETower(towerTexture, "AOE Tower", click_position.x, click_position.y));
                            playerMoney -= 150; // decrease money
                        }
                    } else { // if an occupied square is selected, force all towers to attack
                        if (map.get_enemies().size() > 0) {
                            firstEnemyPosition = map.get_enemies()[0]->get_object().getPosition(); // get the position of first enemy for visuals
                        }
                        map.towers_attack(); // all towers attack
                        srand(time(NULL));
                        errorText = rand() % 10; // set error message for drawing
                        errorMessageCountdown = 200;
                    }                 
                }

            // logic for changing tower selection    
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
                towerSelection = 1; // ranged tower selection
                last_input_1 = true;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
                towerSelection = 2; // AOE tower selection
                last_input_1 = false;
            }
        }

        // Clear the window before drawing any objects
        window.clear(sf::Color::White);

        // Draw the ground grid
        for (int i = 0; i < gridSize; ++i) {
            for (int j = 0; j < gridSize; ++j) {
                window.draw(grid[i][j]);
            }
        }

        // draw on-screen GUI
        window.draw(visibleMoney);
        window.draw(visibleScore);
        window.draw(visibleHighscore);
        window.draw(towerCosts);

        // draw tower selection
        if (last_input_1 == true) {
            towerUI.setTexture(towerPointer1);
            window.draw(towerUI);
        } else if (last_input_1 == false) {
            towerUI.setTexture(towerPointer2);
            window.draw(towerUI);
        }

        // delete dead enemies
        bool gameOver = false; // variable for determining if the game is over
        for (int i=0; i<map.get_enemies().size(); i++) {
            if (map.get_enemies()[i]->get_object().getPosition().y > 800) {
                map.remove_enemy(map.get_enemies()[i]);
                game_over = true; // end game if enemy reaches the bottom of the screen

            } else if (map.get_enemies()[i]->get_health() <= 0) {
                playerMoney += 100;
                map.remove_enemy(map.get_enemies()[i]); // remove enemy if killed by tower
                playerMoney += 100;
                score += 100;
            }
        }

        // update money every frame
        moneyDisplay = to_string(playerMoney);
        visibleMoney.setString("$" + moneyDisplay);

        // update score every frame
        scoreDisplay = to_string(score);
        visibleScore.setString("Score: " + scoreDisplay);

        // update highscore every frame
        if (score > highscore) {
            highscoreDisplay = to_string(score);
            visibleHighscore.setString("Highscore: " + highscoreDisplay);
        }

        // draw fast forwards
        if (clockInterval == 500) {
            window.draw(fastForward);
        }
        
        // handle game ending
        while (game_over == true) {

            // draw window objects
            menuTitle.setString("Game Over!");
            menuTitle.setPosition(180,250);
            for (int i = 0; i < gridSize; ++i) {
                for (int j = 0; j < gridSize; ++j) {
                    window.draw(grid[i][j]);
                }
            }
            window.draw(menuTitle);
            window.display();

            // if the score is higher than the highest, rewrite the highscore
            if (score > highscore) {
                highscoreFile.open("text/highscoreStorage.txt", ios::out); // append (add on)
                if (highscoreFile.is_open()) { // if the file is open
                    highscoreFile << score << endl; // write test to a file
                    highscoreFile.close(); // close the file
                }
            }

            // poll for events and close window
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
        if (clock % attackPeriod == 0) {

            // update the position of the first enemy only when an attack begins
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

        // draw a random 'error' message when the user selects an occupied grid
        if (errorMessageCountdown > 0) {
            
            // select a random message every second
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
            
            // draw the writing to the window
            errorMessage.setFillColor(sf::Color(250,250,250,errorMessageCountdown+50));
            window.draw(errorMessage);
            errorMessageCountdown--;
        }
    
        // Update the window
        window.display();

        // Handle escape keypress for pause menu
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && (pause == false)) {
            window.draw(transparent);
            window.draw(backdrop);
            window.display();
            pause = true;
            lock_input = true;
        }
        
        // pause menu event loop
        while (pause == true) {
            
            // Poll for events, resets inputs so they aren't retroactively registered
            while (window.pollEvent(event)) {}
            
            // lock the input to prevent multiple clicks
            while (lock_input == true) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) == false && lock_input == true) {
                    lock_input = false;
                }
            }

            // Close the window if close button is clicked
            if (event.type == sf::Event::Closed) {
                window.close();   
                return 0; 
            }

            // If the user presses escape show the pause menu
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && (pause == true)) {
                // lock the input until they release escape
                lock_input = true;
                
                // error handling to stop escape being held
                while (lock_input == true) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) == false && lock_input == true) {
                    // unlock input
                    lock_input = false;
                    }
                }
                    // Set pause to false
                    pause = false;
            }

            // check if user presses a menu button and output accordingly
            sf::Vector2i menu_click_position = sf::Mouse::getPosition(window);
            
            if(event.type == sf::Event::MouseButtonPressed) { // check for mouse click
                if (menu_click_position.x >= 282 && menu_click_position.x <= 517) {  // pause menu coordinates
                    if (menu_click_position.y >= 245 && menu_click_position.y <= 333) { // pause menu coordinates
                        pause = false;

                    // Write the high-score to a file if selected
                    } else if (menu_click_position.y >= 345 && menu_click_position.y <= 433) {
                        scoreFile.open("text/saveStorage.txt", ios::out); // write to file
                        if (scoreFile.is_open()) { // if the file is open

                            scoreFile << score << endl; // write test to a file
                            scoreFile.close(); // close the file
                        }
                        if (score > highscore) {
                            highscoreFile.open("text/highscoreStorage.txt", ios::out); // append (add on)
                            
                            if (highscoreFile.is_open()) { // if the file is open
                                highscoreFile << score << endl; // write high score to a file
                                highscoreFile.close(); // close the file
                            }
                        }

                    // Close the window if exit is selected    
                    } else if (menu_click_position.y >= 445 && menu_click_position.y <= 533) {
                        // end the game
                        window.close();   
                        return 0; 
                    }
                }
            }
        }
    }

    return 0;
}