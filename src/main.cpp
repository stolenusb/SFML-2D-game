#include <SFML\Graphics.hpp>
#include <iostream>

#include "player.h"
#include "platform.h"

int main()
{
    // ------------------- INITIALIZATION --------------------
    sf::Vector2f windowSize(1280.0f, 720.0f);
    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "GameProject");
    sf::Clock clock;
    double deltaTime = 0.0f;

    Player player;
    
    Platform background("background.jpg", windowSize, sf::Vector2f(0.0f, 0.0f));
    Platform ground("ground.jpg", sf::Vector2f(windowSize.x, 175.0f), sf::Vector2f(0.0f, windowSize.y - 175.0f));

    Platform platform_1("", sf::Vector2f(150.0f, 40.0f), sf::Vector2f(200.0f, 520.0f));
    Platform platform_2("", sf::Vector2f(150.0f, 40.0f), sf::Vector2f(400.0f, 420.0f));
    Platform platform_3("", sf::Vector2f(150.0f, 40.0f), sf::Vector2f(600.0f, 320.0f));

    // ------------------- GAME LOOP ----------------------
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
            
            player.Jumped(event);
        }

        // ------------------- PLAYER ----------------------
        deltaTime = clock.restart().asSeconds();
        player.Update(deltaTime);
        // Player collision with platforms.
        player.collider.checkCollision(ground.Entity);
        player.collider.checkCollision(platform_1.Entity);
        player.collider.checkCollision(platform_2.Entity);
        player.collider.checkCollision(platform_3.Entity);

        // ------------------- RENDER ----------------------
        window.clear(sf::Color::Black);

        window.draw(background.Entity);
        window.draw(ground.Entity);
        window.draw(platform_1.Entity);
        window.draw(platform_2.Entity);
        window.draw(platform_3.Entity);

        player.Draw(window);

        window.display();
    }

    return 0;
}