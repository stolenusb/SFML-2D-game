#include "player.h"

Player::Player(sf::Vector2f playerSize, double moveSpeed, double jumpForce) :
    playerSize(playerSize),
    moveSpeed(moveSpeed),
    jumpForce(jumpForce),
    animation(Sprite, 128),
    animationBullet(Bullet, 64),
    collider(Entity, Sprite, Velocity)
{
    setPosition(50.f, 433.f);

    Entity.setSize(playerSize);
    Entity.setFillColor(sf::Color::Transparent);
    //For debug only:
    //Entity.setOutlineThickness(3.0f);
    loadTextures();  
}

Player::~Player()
{
}

void Player::loadTextures()
{
    if( !Texture[PLAYER_IDLE].loadFromFile("..\\assets\\textures\\magician\\idle.png") ||
        !Texture[PLAYER_WALK].loadFromFile("..\\assets\\textures\\magician\\walk.png") ||
        !Texture[PLAYER_RUN].loadFromFile("..\\assets\\textures\\magician\\run.png") ||
        !Texture[PLAYER_JUMP].loadFromFile("..\\assets\\textures\\magician\\jump.png") ||
        !Texture[PLAYER_ATTACK].loadFromFile("..\\assets\\textures\\magician\\attack_1.png") ||
        !Texture[PLAYER_BULLET].loadFromFile("..\\assets\\textures\\magician\\charge_1.png"))

        std::cout << "(-) Failed to load one of the player textures." << std::endl;
    else
        std::cout << "(+) Loaded player textures." << std::endl;
}

void Player::Update()
{
    double deltaTime = clock.restart().asSeconds();

    // Frame Initialization
    if(collider.bCollidingWithGround)
        Velocity.x = 0.f;
    
    Velocity.y += 9.8f;

    animation.Set(Texture[PLAYER_IDLE], 8);

    // Input
    Input();

    // Update
    animation.Animate();
    animationBullet.Animate();

    Entity.move(Velocity.x * deltaTime, Velocity.y * deltaTime);
    Sprite.move(Velocity.x * deltaTime, Velocity.y * deltaTime);

    if(bulletAttack) {
        bulletVelocity += 5.f;
        Bullet.move(bulletVelocity * deltaTime, 0.f);
    }
}

void Player::Input()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        setPosition(50.f, 433.f);
    
    if(collider.bCollidingWithGround)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            animation.lookRight = true;
            Velocity.x = moveSpeed;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            animation.lookRight = false;
            Velocity.x = -moveSpeed;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))) {
            animation.Set(Texture[PLAYER_RUN], 8);
            Velocity.x *= 2.5f;
        }

        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)))
            animation.Set(Texture[PLAYER_WALK], 7);
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            Velocity.x = 0.f;
            animation.Set(Texture[PLAYER_ATTACK], 7);

            bulletAttack = true;
            bulletVelocity = 0.f;
            Bullet.setPosition(Sprite.getPosition());
            animationBullet.Set(Texture[PLAYER_BULLET], 9);
        }
    }

    else
        animation.Set(Texture[PLAYER_JUMP], 8);
}

void Player::Jump()
{
    Velocity.y -= jumpForce;
    collider.bCollidingWithGround = false;
}

void Player::Draw(sf::RenderWindow &window)
{
    window.draw(Sprite);
    window.draw(Entity);
    window.draw(Bullet);
}

void Player::setPosition(double x, double y)
{
    Entity.setPosition(x, y);
    Sprite.setPosition(x - playerSize.x, y - playerSize.y);
}