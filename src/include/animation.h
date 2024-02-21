#pragma once

#include <SFML\Graphics.hpp>

enum TEXTURES
{
    PLAYER_IDLE = 0,
    PLAYER_WALK = 1,
    PLAYER_RUN = 2,
    PLAYER_JUMP = 4,
    TEXTURE_COUNT
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
    sf::Texture playerTextures[TEXTURE_COUNT];
    sf::Sprite *playerSprite;
    unsigned int imageSize;
    unsigned int imgCount;
    unsigned int currImage;
    sf::IntRect rect;
    sf::Clock clock;
};