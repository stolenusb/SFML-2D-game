#include <SFML\Graphics.hpp>

#include "player.h"
#include "enemy.h"
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
    const sf::Vector2f entitySize = sf::Vector2f(42.f, 64.f);

    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "GameProject");
    window.setFramerateLimit(60);

        // ------- Player --------
    const float moveSpeed = 100.f;
    const float jumpForce = 400.f;
    
    Player player(window, entitySize, moveSpeed, jumpForce);
        // ------- Enemy ---------
    Enemy enemy(entitySize, 750.f);
    Enemy enemy1(entitySize, 900.f);

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
        
        // ------------------- ENTITIES ----------------------
        player.Update();
        enemy.Update();
        enemy1.Update();

        // Entity collision with platforms.
        for(int i = 0; i < PLATFORM_COUNT; i++) {
            player.collider.checkCollision(platforms[i].Entity);
            enemy.collider.checkCollision(platforms[i].Entity);
            enemy1.collider.checkCollision(platforms[i].Entity);
        }   

        // ------------------- RENDER ----------------------
        // Clearing frame
        window.clear(sf::Color::Black);

        // Platforms Render
        window.draw(background.Entity);

        for(int i = 0; i < PLATFORM_COUNT; i++)
            window.draw(platforms[i].Entity);

        // Entity render  
        player.Draw();
        enemy.Draw(window);
        enemy1.Draw(window);
        
        // Displaying frame.
        window.display();
    }

    return 0;
}