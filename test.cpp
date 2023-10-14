#include <iostream>
#include <time.h>

// Standard libraries
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <cmath>

// SFML modules and libraries
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace std;
int main() {

    
    sf::Font(font);
    sf::Text text;
    text.setFont(font);
    text.setString("Hello World");
    text.setCharacterSize(200);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
}