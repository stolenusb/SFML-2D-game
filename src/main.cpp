#include <SFML\Graphics.hpp>

#include "player.h"
#include "platform.h"

enum PLATFORMS {
    PLATFORM_GROUND,
    PLATFORM_ONE,
    PLATFORM_TWO,
    PLATFORM_THREE,
    PLATFORM_COUNT
};

int main()
{
    // -------------------------------------------------- INITIALIZATION ------------------------------------------------------------
        // ------- Window -------
    sf::Vector2f windowSize(1280.f, 720.f);

    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "GameProject");
    window.setFramerateLimit(60);

        // ------- Player --------
    const sf::Vector2f playerSize = sf::Vector2f(42.f, 64.f);
    const double moveSpeed = 100.f;
    const double jumpForce = 400.f;
    
    Player player(playerSize, moveSpeed, jumpForce);

        // ------- Platforms -----
    Platform background("background.jpg", windowSize, sf::Vector2f(0.f, 0.f));
    Platform platforms[PLATFORM_COUNT] = {
        Platform("ground.jpg", sf::Vector2f(windowSize.x, 175.f), sf::Vector2f(0.f, windowSize.y - 175.f)),
        Platform("", sf::Vector2f(150.f, 40.f), sf::Vector2f(200.f, 520.f)),
        Platform("", sf::Vector2f(150.f, 40.f), sf::Vector2f(400.f, 420.f)),
        Platform("", sf::Vector2f(150.f, 40.f), sf::Vector2f(600.f, 320.f))
    };

    // ---------------------------------------------------- GAME LOOP -----------------------------------------------------------------
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {   
            if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();

            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && player.collider.bCollidingWithGround) {
                player.Jump();
            }
        }

        // ------------------- PLAYER ----------------------
        player.Update();

        // Player collision with platforms.
        for(int i = 0; i < PLATFORM_COUNT; i++)
            player.collider.checkCollision(platforms[i].Entity);

        // ------------------- RENDER ----------------------
        // Clearing frame
        window.clear(sf::Color::Black);

        // Platforms Render
        window.draw(background.Entity);

        for(int i = 0; i < PLATFORM_COUNT; i++)
            window.draw(platforms[i].Entity);

        // Player render  
        player.Draw(window);
        
        // Displaying frame.
        window.display();
    }

    return 0;
}