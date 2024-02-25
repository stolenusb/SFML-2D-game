#pragma once

#include <SFML\Graphics.hpp>

enum PLAYER_TEXTURES
{
    PLAYER_IDLE,
    PLAYER_WALK,
    PLAYER_RUN,
    PLAYER_JUMP,
    PLAYER_TEXTURES_COUNT
};

class Animation 
{
public:
    Animation(sf::Sprite &playerSprite, unsigned int playerSize);
    ~Animation();

    void loadTextures();
    void Animate();
    void Set(unsigned int texture, unsigned int imageCount);

    bool lookRight =  true;

private:
    sf::Sprite &playerSprite;
    sf::Texture playerTextures[PLAYER_TEXTURES_COUNT];
    sf::IntRect textureRect;
    sf::Clock clock;
    unsigned int imageSize;
    unsigned int imgCount;
    unsigned int currImage;
};