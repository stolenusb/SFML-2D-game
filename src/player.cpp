#include "player.h"
#include "math.h"

Player::Player() :
    animation(Sprite, 128)
{
    Sprite.setPosition(sf::Vector2f(50, 720 - 175 - 128));
    animation.loadTextures();
}

Player::~Player()
{
}

void Player::Draw(sf::RenderWindow &window)
{
    window.draw(Sprite);
    window.draw(entity);
}

void Player::Update(double deltaTime)
{
    moveSpeed = 0.2f;
    jumpSpeed = 5.0f;

    animation.Set(PLAYER_IDLE, 7);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        Sprite.setPosition(sf::Vector2f(50, 720 - 175 - 128));

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) && canJump) {
        animation.Set(PLAYER_RUN, 7);
        moveSpeed *= 2.0f;
    }

    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) && canJump)
        animation.Set(PLAYER_WALK, 6);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        animation.lookRight = true;
        Velocity.x = moveSpeed * deltaTime;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        animation.lookRight = false;
        Velocity.x = -moveSpeed * deltaTime;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        Velocity.y = jumpSpeed * deltaTime;
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        Velocity.y = -jumpSpeed * deltaTime;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump )
    {
        canJump = false;
        Velocity.y = -jumpSpeed * deltaTime;
    }

    if(Sprite.getPosition().y + 128 < (720 - 128) || Velocity.y < 0)
        Velocity.y += 0.5f * deltaTime;
    else {
        Sprite.setPosition(Sprite.getPosition().x, 720 - 175 - 127);
        canJump = true;
        Velocity.y = 0;
    }

    animation.Animate();
    Sprite.move(Velocity.x, Velocity.y);
    Velocity.x = 0;
}