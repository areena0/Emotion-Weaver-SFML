#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include <memory>

// Animation data for a single sprite sheet
struct Animation
{
    sf::Texture* texture;
    int frameCount;
    int frameWidth;
    int frameHeight;
    float frameDuration;  // Seconds per frame
    bool loop;
    
    Animation()
        : texture(nullptr), frameCount(0), frameWidth(0), frameHeight(0)
        , frameDuration(0.1f), loop(true)
    {}
    
    Animation(sf::Texture* tex, int frames, float duration = 0.1f, bool shouldLoop = true)
        : texture(tex), frameCount(frames), frameDuration(duration), loop(shouldLoop)
    {
        if (texture)
        {
            frameWidth = texture->getSize().x / frames;
            frameHeight = texture->getSize().y;
        }
        else
        {
            frameWidth = 0;
            frameHeight = 0;
        }
    }
};

// Animated sprite that plays sprite sheet animations
class AnimatedSprite
{
public:
    AnimatedSprite();
    
    // Add an animation with a name
    void addAnimation(const std::string& name, const Animation& anim);
    
    // Play a specific animation
    void play(const std::string& name, bool restart = false);
    
    // Update animation (call every frame)
    void update(float deltaTime);
    
    // Draw the current frame
    void draw(sf::RenderWindow& window);
    
    // Transform controls
    void setPosition(const sf::Vector2f& pos);
    void setScale(const sf::Vector2f& scale);
    void setColor(const sf::Color& color);
    
    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;
    
    // Animation state
    bool isPlaying() const { return playing; }
    bool hasFinished() const { return finished; }
    std::string getCurrentAnimation() const { return currentAnimName; }
    
private:
    void updateFrame();
    
    std::unordered_map<std::string, Animation> animations;
    std::string currentAnimName;
    Animation* currentAnim;
    
    std::unique_ptr<sf::Sprite> sprite;
    sf::IntRect currentFrameRect;
    
    int currentFrame;
    float frameTimer;
    bool playing;
    bool finished;
    
    sf::Vector2f position;
    sf::Vector2f scale;
    sf::Color color;
    
    int baseFrameHeight;  // Reference frame height for alignment
};
