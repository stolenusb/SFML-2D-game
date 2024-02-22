#include "player.h"
#include "math.h"

Player::Player() :
    animation(Sprite, 128)
{
    Sprite.setPosition(sf::Vector2f(50, 433));
    animation.loadTextures();
}

Player::~Player()
{
}

void Player::Draw(sf::RenderWindow &window)
{
    window.draw(Sprite);
}

void Player::Jumped(sf::Event &event)
{
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && !Jumping ) {
        Jumping = true;
        Velocity.y -= jumpForce / 45;
    }
}

void Player::Update(double deltaTime)
{
    animation.Set(PLAYER_IDLE, 8);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        Sprite.setPosition(sf::Vector2f(50, 433));

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) && !Jumping) {
        animation.Set(PLAYER_RUN, 8);
        moveSpeed = 300.0f;
    }

    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) && !Jumping) {
        animation.Set(PLAYER_WALK, 7);
        moveSpeed = 200.0f;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        animation.lookRight = true;
        Velocity.x = moveSpeed * deltaTime;
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        animation.lookRight = false;
        Velocity.x = -moveSpeed * deltaTime;
    }

    if(Jumping) {
        animation.Set(PLAYER_JUMP, 8);
        Velocity.y += 9.8f * deltaTime;
        Sprite.move(0, Velocity.y);

        if(Sprite.getPosition().y > 433.0f) {
            Sprite.setPosition(Sprite.getPosition().x, 433.0f);
            Jumping = false;
        }
    }

    animation.Animate();
    Sprite.move(Velocity.x, 0);
    Velocity.x = 0.0;
}