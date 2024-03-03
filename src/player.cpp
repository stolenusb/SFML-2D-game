#include "player.h"

Player::Player(sf::RenderWindow &window, sf::Vector2f playerSize, double moveSpeed, double jumpForce) :
    window(window),
    playerSize(playerSize),
    moveSpeed(moveSpeed),
    jumpForce(jumpForce),
    animation(Sprite, 128),
    collider(Entity, Sprite, Velocity),
    projectile(window, Entity, Texture[PLAYER_PROJECTILE])
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
        !Texture[PLAYER_PROJECTILE].loadFromFile("..\\assets\\textures\\magician\\charge_1.png"))

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

    Entity.move(Velocity.x * deltaTime, Velocity.y * deltaTime);
    Sprite.move(Velocity.x * deltaTime, Velocity.y * deltaTime);

    // Update Projectiles
    for(int i = 0; i < projectiles.size(); i++)
        projectiles[i].Move(projectileSpeed, deltaTime);
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
        
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            Shoot();
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

void Player::Shoot()
{
    Velocity.x = 0.f;
    animation.Set(Texture[PLAYER_ATTACK], 7);
    
    projectiles.push_back(projectile);
    projectiles[projectiles.size() - 1].Set();
}

void Player::Draw()
{
    for(int i = 0; i < projectiles.size(); i++)
        projectiles[i].Draw();
    
    window.draw(Sprite);
    window.draw(Entity);
}

void Player::setPosition(double x, double y)
{
    Entity.setPosition(x, y);
    Sprite.setPosition(x - playerSize.x, y - playerSize.y);
}