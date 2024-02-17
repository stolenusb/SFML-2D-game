#include <SFML\Graphics.hpp>
#include <iostream>

sf::Vector2u windowSize(1280, 720);

#include "animation.h"

int main()
{
    // ------------------- INITIALIZATION --------------------
    sf::Vector2f fplayerSize(128, 128);
    sf::Vector2f fgroundSize(windowSize.x, 175);
    sf::Clock clock;
    
    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "GameProject");

    const float gravity = 5;
    sf::Vector2f velocity(sf::Vector2f(0, 0));

    // ------------------- PLAYER --------------------
    sf::Texture playerTexture;
    sf::Texture playerTextureRun;
    sf::Sprite player;
    sf::Vector2f playerVelocity(sf::Vector2f(0, 0));
    Animation playerAnim;
    
    if(playerTexture.loadFromFile("..\\assets\\textures\\magician\\idle.png") && playerTextureRun.loadFromFile("..\\assets\\textures\\magician\\walk.png"))
        std::cout << "(+) Loaded player texture." << std::endl;
        
    else if(!playerTexture.loadFromFile("..\\assets\\textures\\magician\\idle.png") || !playerTextureRun.loadFromFile("..\\assets\\textures\\magician\\walk.png")) {
        std::cout << "(-) Failed to load player texture" << std::endl;

        return 1;
    }

    player.setPosition(sf::Vector2f(50, windowSize.y - fgroundSize.y - 64));
    playerAnim.Set(&player, 7, sf::Vector2u(128, 128));

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
            if(event.type == sf::Event::Closed)
                window.close();
        }
        
        player.setOrigin(player.getLocalBounds().width/2, player.getLocalBounds().height/2);
        player.setTexture(playerTexture);

        // ------------------- INPUT -------------
        float moveSpeed = 0.2 * clock.getElapsedTime().asMilliseconds();
        float jumpSpeed = 1 * clock.getElapsedTime().asMilliseconds();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            player.setTexture(playerTextureRun);
            player.setScale(1, 1);
            playerVelocity.x = moveSpeed;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            player.setTexture(playerTextureRun);
            player.setScale(-1, 1);
            playerVelocity.x = -moveSpeed;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            //player.setTexture(playerTextureRun);
            //player.setScale(-1, 1);
            playerVelocity.y = -jumpSpeed;
        }
        
        if(player.getPosition().y < ground.getPosition().y - 64)
            playerVelocity.y += gravity;
        else
            player.setPosition(player.getPosition().x, ground.getPosition().y - 64);

        player.move(playerVelocity.x, playerVelocity.y);

        playerVelocity = sf::Vector2f(0, 0);
        clock.restart();

        // ------------------- RENDER -------------
        window.clear(sf::Color::Black);
        playerAnim.Animate();
        window.draw(background);
        window.draw(ground);
        window.draw(player);

        window.display();
    }

    return 0;
}