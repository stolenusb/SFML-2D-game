#include <SFML\Graphics.hpp>
#include <iostream>

sf::Vector2u windowSize(1280, 720);

#include "player.h"

int main()
{
    // ------------------- INITIALIZATION --------------------
    sf::Vector2f fgroundSize(windowSize.x, 175);
    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "GameProject");
    sf::Clock clock;
    double deltaTime = 0.0f;

    Player player;

    // ------------------- MAP GROUND --------------------  
    sf::RectangleShape ground(fgroundSize);
    sf::Texture groundTexture;
    
    if(groundTexture.loadFromFile("..\\assets\\textures\\ground.jpg")) {
        ground.setTexture(&groundTexture);
        std::cout << "(+) Loaded ground texture." << std::endl;
    } else if(!groundTexture.loadFromFile("..\\assets\\textures\\ground.jpg")) {
        ground.setFillColor(sf::Color::Green);
        std::cout << "(-) Failed to load ground texture" << std::endl;
    }

    ground.setPosition(sf::Vector2f(0, windowSize.x - windowSize.y));

    // ------------------- BACKGROUND TEXTURE -------------
    sf::RectangleShape background(sf::Vector2f(windowSize.x, windowSize.y));
    sf::Texture backgroundTexture;

    if(backgroundTexture.loadFromFile("..\\assets\\textures\\background.jpg")) {
        background.setTexture(&backgroundTexture);
        std::cout << "(+) Loaded background texture." << std::endl;
    } else if(!backgroundTexture.loadFromFile("..\\assets\\textures\\background.jpg")) {
        background.setFillColor(sf::Color::Blue);
        std::cout << "(-) Failed to load background texture" << std::endl;
    }

    // ------------------- GAME LOOP -------------
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }

        // ------------------- PLAYER -------------
        deltaTime = clock.restart().asMilliseconds();
        player.Update(deltaTime);

        // ------------------- RENDER -------------
        window.clear(sf::Color::Black);

        window.draw(background);
        window.draw(ground);
        player.Draw(window);

        window.display();
    }

    return 0;
}