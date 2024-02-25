#include "animation.h"

Animation::Animation(sf::Sprite &Sprite, unsigned int animationSize) :
    Sprite(Sprite)
{
    textureRect = sf::IntRect(0, 0, animationSize, animationSize);
}

Animation::~Animation()
{
}

void Animation::Set(sf::Texture &texture, unsigned int imageCount)
{   
    imgCount = imageCount - 1;
    Sprite.setTexture(texture);
}

void Animation::Animate()
{
    // Changing animation image every 0.14 sec
    if(clock.getElapsedTime().asSeconds() > 0.14f) {
        // If reached last animation image, initialize animation
        if(currImage >= imgCount)
            currImage = 0;
        else // Else set to next animation image
            currImage++;

        clock.restart();
    }

    //if looking right, flip image
    if(lookRight == true) {
        textureRect.width = abs(textureRect.width);
        textureRect.left = currImage * textureRect.width;
    } else { // vice versa
        textureRect.width = -abs(textureRect.width);
        textureRect.left = (currImage + 1) * abs(textureRect.width);
    }
        
    Sprite.setTextureRect(textureRect);
}