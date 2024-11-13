#include "player.h"
#include "enemy.h"
#include "platform.h"

int main()
{
    // -------------------------------------------------- INITIALIZATION ------------------------------------------------------------
        // ------- Window -------
    sf::Vector2f windowSize(1280.f, 720.f);
    const sf::Vector2f entitySize = sf::Vector2f(42.f, 64.f);

    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "GameProject");
    window.setFramerateLimit(60);

        // ------ Main Menu ------
    sf::Font font;
    sf::Text PlayButton;

    if (!font.loadFromFile("..\\..\\assets\\font\\dynamictrooper.ttf"))
        std::cout << "(-) Failed to load font" << std::endl;
    
    sf::Vector2i PlayButtonPos(sf::Vector2i(100, 50));
    PlayButton.setPosition(sf::Vector2f(PlayButtonPos));
    PlayButton.setCharacterSize(100);
    PlayButton.setFont(font);
    PlayButton.setFillColor(sf::Color::White);
    PlayButton.setStyle(sf::Text::Bold);
    PlayButton.setLetterSpacing(1.5f);
    PlayButton.setString("PLAY");
    bool bMainMenu = true;
    
        // ------- Player --------
    const float moveSpeed = 100.f;
    const float jumpForce = 400.f;
    
    Player player(window, entitySize, moveSpeed, jumpForce);
        // ------- Platforms -----
    Platform background("background.jpg", windowSize, sf::Vector2f(0.f, 0.f));
    Platform object[OBJECT_COUNT] = {
        Platform("ground.jpg", sf::Vector2f(windowSize.x, 175.f), sf::Vector2f(0.f, windowSize.y - 175.f)),
        Platform("", sf::Vector2f(150.f, 40.f), sf::Vector2f(200.f, 520.f)),
        Platform("", sf::Vector2f(150.f, 40.f), sf::Vector2f(400.f, 420.f)),
        Platform("", sf::Vector2f(150.f, 40.f), sf::Vector2f(600.f, 320.f))
    };

            // ------- Enemy ---------
    Enemy enemy(entitySize, 750.f);

    // ---------------------------------------------------- GAME LOOP -----------------------------------------------------------------
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {   
            if(event.type == sf::Event::Closed)
                window.close();
            
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !bMainMenu)
                bMainMenu = true;

            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && player.collider.bCollidingWithGround) {
                player.Jump();
            }
        }
        
        // Load Main Menu
        if(bMainMenu)
        {
            // If Mouse position on play button.
            if(     sf::Mouse::getPosition(window).x >= PlayButtonPos.x && sf::Mouse::getPosition(window).x <= (PlayButtonPos.x + 200.f) &&
                    sf::Mouse::getPosition(window).y >= PlayButtonPos.y && sf::Mouse::getPosition(window).y <= (PlayButtonPos.y + 100.f)    )
            {
                PlayButton.setFillColor(sf::Color::Blue);
                    // Exit Main Menu
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                        bMainMenu = false;
            } else
                PlayButton.setFillColor(sf::Color::White);
            
            // Clearing frame
            window.clear(sf::Color::Black);
            window.draw(PlayButton);
        }

        // Resume Game if Exited main menu
        else {
            // ------------------- ENTITIES ----------------------
            player.Update();
            enemy.Update();

            // Entity collision with other objects/entities.
            for(int i = 0; i < OBJECT_COUNT; i++) {
                player.collider.checkCollision(object[i].Entity);
                enemy.collider.checkCollision(object[i].Entity);
            }

            player.projectile1.checkCollision(enemy);
            player.projectile2.checkCollision(enemy);

            // ------------------- RENDER ----------------------
            // Clearing frame
            window.clear(sf::Color::Black);

            // Objects Render
            window.draw(background.Entity);

            for(int i = 0; i < OBJECT_COUNT; i++)
                window.draw(object[i].Entity);

            // Entity render  
            player.Draw();
            enemy.Draw(window);
        }
        
        // Displaying frame.
        window.display();
    }

    return 0;
}