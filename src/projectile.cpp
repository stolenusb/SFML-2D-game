#include "projectile.h"

void Projectile::Update(double deltaTime)
{
    for(int i = 0; i < proj.size(); i++) {
        proj.at(i).anim.Animate(proj.at(i).sprite);
            
        proj.at(i).entity.move(projectileSpeed * cos(proj.at(i).angle) * deltaTime, projectileSpeed * sin(proj.at(i).angle) * deltaTime);
        proj.at(i).sprite.move(projectileSpeed * cos(proj.at(i).angle) * deltaTime, projectileSpeed * sin(proj.at(i).angle) * deltaTime);
        
        if( proj.at(i).entity.getPosition().x <= 0.f ||
            proj.at(i).entity.getPosition().y <= 0.f ||
            proj.at(i).entity.getPosition().x >= 1280.f - 64.f ||
            proj.at(i).entity.getPosition().y >= 720.f - 64.f )
        {
            proj.at(i).sprite.setColor(sf::Color::Transparent);
            proj.erase(proj.begin() + i);
        }
    }
}

void Projectile::Add(sf::Vector2i windowPos, sf::Vector2f playerPos, unsigned int projTextureID, unsigned int count, float projSpeed)
{
    projectileSpeed = projSpeed;
    playerPos = sf::Vector2f(playerPos.x + 20.f, playerPos.y + 20.f);
    sf::Vector2f projectilePos = sf::Vector2f(windowPos.x - playerPos.x, windowPos.y - playerPos.y);
    added_proj.angle = atan2(projectilePos.y, projectilePos.x);

    added_proj.entity.setSize(sf::Vector2f(64.f, 64.f));
    //added_proj.entity.setOutlineThickness(1.f);
    added_proj.entity.setFillColor(sf::Color::Transparent);
    added_proj.entity.setPosition(playerPos.x + 15.f, playerPos.y + 64.f);

    added_proj.sprite.setPosition(playerPos);
    added_proj.sprite.setScale(1.5f, 1.5f);

    added_proj.anim.loadTextures(PROJECTILE_ANIM);
    added_proj.anim.Set(projTextureID, count, sf::Vector2u(64, 128));

    proj.push_back(added_proj);
}

void Projectile::checkCollision(Enemy &enemy)
{
    for(int i = 0; i < proj.size(); i++)
        if(enemy.collider.checkCollision(proj.at(i).entity)) {
            proj.at(i).sprite.setColor(sf::Color::Transparent);
            proj.erase(proj.begin() + i);

            enemy.Hurt(15.f);
        }
}

void Projectile::Draw(sf::RenderWindow &window)
{
    for(int i = 0; i < proj.size(); i++) {
        window.draw(proj.at(i).sprite);
        window.draw(proj.at(i).entity);
    }
}