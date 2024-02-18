#include "player.h"

Player::Player() :
    animation(Sprite, 128)
{
    Sprite.setPosition(sf::Vector2f(50, 1280 - 720 - 64));
    animation.loadTextures();
}

Player::~Player()
{
}

void Player::Update(double deltaTime)
{
    float moveSpeed = 0.2f * deltaTime;
    float jumpSpeed = 1.0f * deltaTime;
    animation.Set(PLAYER_IDLE, 7);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))) {
        animation.Set(PLAYER_RUN, 7);
        moveSpeed *= 2;
    }

    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)))
        animation.Set(PLAYER_WALK, 6);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        Sprite.setPosition(sf::Vector2f(50, 1280 - 720 - 64));

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        animation.lookRight = true;
        Velocity.x = moveSpeed;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        animation.lookRight = false;
        Velocity.x = -moveSpeed;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        Velocity.y = -jumpSpeed;
    
    animation.Animate();
    Sprite.move(Velocity);
    Velocity = sf::Vector2f(0, 0);
}