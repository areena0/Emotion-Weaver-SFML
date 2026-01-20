#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite()
    : currentAnim(nullptr)
    , currentFrame(0)
    , frameTimer(0.0f)
    , playing(false)
    , finished(false)
    , position(0.f, 0.f)
    , scale(1.f, 1.f)
    , color(sf::Color::White)
    , baseFrameHeight(0)
{
}

void AnimatedSprite::addAnimation(const std::string& name, const Animation& anim)
{
    animations[name] = anim;
    
    // Store the IDLE animation's frame height as the base reference
    // All other animations will be aligned relative to this
    if (name == "Idle" && anim.frameHeight > 0)
    {
        baseFrameHeight = anim.frameHeight;
    }
    // If Idle hasn't been added yet, use the first animation
    else if (baseFrameHeight == 0 && anim.frameHeight > 0)
    {
        baseFrameHeight = anim.frameHeight;
    }
}

void AnimatedSprite::play(const std::string& name, bool restart)
{
    auto it = animations.find(name);
    if (it == animations.end())
    {
        return; // Animation not found
    }
    
    // If already playing this animation and not restarting, continue
    if (currentAnimName == name && !restart && playing)
    {
        return;
    }
    
    currentAnimName = name;
    currentAnim = &it->second;
    currentFrame = 0;
    frameTimer = 0.0f;
    playing = true;
    finished = false;
    
    // Create or update sprite with the animation's texture
    if (currentAnim->texture)
    {
        if (!sprite)
        {
            sprite = std::make_unique<sf::Sprite>(*currentAnim->texture);
        }
        else
        {
            sprite->setTexture(*currentAnim->texture);
        }
        
        updateFrame();
        
        sprite->setPosition(position);
        sprite->setScale(scale);
        sprite->setColor(color);
    }
}

void AnimatedSprite::update(float deltaTime)
{
    if (!playing || !currentAnim || finished)
        return;
    
    frameTimer += deltaTime;
    
    // Check if it's time to advance to next frame
    if (frameTimer >= currentAnim->frameDuration)
    {
        frameTimer -= currentAnim->frameDuration;
        currentFrame++;
        
        // Check if animation finished
        if (currentFrame >= currentAnim->frameCount)
        {
            if (currentAnim->loop)
            {
                currentFrame = 0; // Loop back to start
            }
            else
            {
                currentFrame = currentAnim->frameCount - 1; // Stay on last frame
                finished = true;
                playing = false;
            }
        }
        
        updateFrame();
    }
}

void AnimatedSprite::updateFrame()
{
    if (!currentAnim || !sprite)
        return;
    
    // Calculate the rectangle for the current frame
    currentFrameRect.position.x = currentFrame * currentAnim->frameWidth;
    currentFrameRect.position.y = 0;
    currentFrameRect.size.x = currentAnim->frameWidth;
    currentFrameRect.size.y = currentAnim->frameHeight;
    
    sprite->setTextureRect(currentFrameRect);
    
    // Set origin to keep character's feet at the same position
    // Use BASE frame height so all animations align at the feet
    sf::Vector2f origin;
    origin.x = currentAnim->frameWidth / 2.f;  // Center horizontally
    
    // Use baseFrameHeight for consistent alignment
    // This ensures character doesn't jump/sink when switching animations
    int referenceHeight = (baseFrameHeight > 0) ? baseFrameHeight : currentAnim->frameHeight;
    origin.y = static_cast<float>(referenceHeight);
    
    sprite->setOrigin(origin);
}

void AnimatedSprite::draw(sf::RenderWindow& window)
{
    if (sprite)
    {
        window.draw(*sprite);
    }
}

void AnimatedSprite::setPosition(const sf::Vector2f& pos)
{
    position = pos;
    if (sprite)
    {
        sprite->setPosition(pos);
    }
}

void AnimatedSprite::setScale(const sf::Vector2f& scl)
{
    scale = scl;
    if (sprite)
    {
        sprite->setScale(scl);
    }
}

void AnimatedSprite::setColor(const sf::Color& col)
{
    color = col;
    if (sprite)
    {
        sprite->setColor(col);
    }
}

sf::Vector2f AnimatedSprite::getPosition() const
{
    return position;
}

sf::FloatRect AnimatedSprite::getGlobalBounds() const
{
    if (sprite)
    {
        return sprite->getGlobalBounds();
    }
    return sf::FloatRect();
}
