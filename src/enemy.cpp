#include "enemy.h"
#include <iostream>

Enemy::Enemy(sf::Vector2f entitySize, float positionX) :
    entitySize(entitySize),
    collider(Entity, Sprite, Velocity)
{
    animation.loadTextures(ENEMY_ANIMS);

    setPosition(positionX, 433.f);

    Entity.setSize(entitySize);
    Entity.setFillColor(sf::Color::Transparent);

    //For debug only:
    Entity.setOutlineThickness(1.0f);

    if (!font.loadFromFile("..\\..\\assets\\font\\dynamictrooper.ttf"))
        std::cout << "(-) Failed to load font" << std::endl;
    
    enemyHP.setCharacterSize(15);
    enemyHP.setFont(font);
    enemyHP.setFillColor(sf::Color::Blue);
    enemyHP.setStyle(sf::Text::Bold);
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
    // Frame Initialization
    if(collider.bCollidingWithGround)
        Velocity.x = 0.f;
    
    Velocity.y += 9.8f;

    Sprite.setColor(sf::Color::White);
    animation.Set(ENEMY_IDLE, 7, sf::Vector2u(128, 128));
    animation.Animate(Sprite);

    enemyHP.setString(std::to_string(Health));

    double deltaTime = clock.restart().asSeconds();
    Entity.move(Velocity.x * deltaTime, Velocity.y * deltaTime);
    Sprite.move(Velocity.x * deltaTime, Velocity.y * deltaTime);
    enemyHP.setPosition(Sprite.getPosition().x + 32.f, Sprite.getPosition().y + 32.f);
}

void Enemy::Hurt(float damage)
{
    Health -= damage;
    animation.Set(ENEMY_HURT, 3, sf::Vector2u(128, 128));
    Sprite.setColor(sf::Color::Red);

    if(Health == 0)
        isDead = true;
}

void Enemy::setPosition(double x, double y)
{
    Entity.setPosition(x, y);
    Sprite.setPosition(x - entitySize.x, y - entitySize.y);
    enemyHP.setPosition(Sprite.getPosition());
}

void Enemy::Draw(sf::RenderWindow &window)
{
    window.draw(Entity);
    window.draw(Sprite);
    window.draw(enemyHP);
}