#include "enemy.h"

Enemy::Enemy(sf::Vector2f entitySize, float positionX) :
    entitySize(entitySize),
    animation(Sprite, 128),
    collider(Entity, Sprite, Velocity)
{
    setPosition(positionX, 433.f);

    Entity.setSize(entitySize);
    Entity.setFillColor(sf::Color::Transparent);

    //For debug only:
    Entity.setOutlineThickness(1.0f);

    loadTextures();
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
    double deltaTime = clock.restart().asSeconds();

    // Frame Initialization
    if(collider.bCollidingWithGround)
        Velocity.x = 0.f;
    
    Velocity.y += 9.8f;

    animation.Set(Texture[ENEMY_IDLE], 7);

    // Update
    animation.Animate();

    Entity.move(Velocity.x * deltaTime, Velocity.y * deltaTime);
    Sprite.move(Velocity.x * deltaTime, Velocity.y * deltaTime);
}

void Enemy::loadTextures()
{
    if(!Texture[ENEMY_IDLE].loadFromFile("..\\assets\\textures\\firewizard\\Idle.png"))
        std::cout << "(-) Failed to load one of the enemy textures." << std::endl;
    else
        std::cout << "(+) Loaded enemy textures." << std::endl;
}

void Enemy::setPosition(double x, double y)
{
    Entity.setPosition(x, y);
    Sprite.setPosition(x - entitySize.x, y - entitySize.y);
}

void Enemy::Draw(sf::RenderWindow &window)
{
    window.draw(Entity);
    window.draw(Sprite);
}