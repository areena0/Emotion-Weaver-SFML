#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <memory>

// Represents a single layer of a background (e.g., sky, clouds, hills)
struct BackgroundLayer
{
    std::unique_ptr<sf::Sprite> sprite;
    std::unique_ptr<sf::Sprite> spriteClone; // For seamless wrapping
    float parallaxSpeed;  // Movement speed multiplier (0.0 = static, 1.0 = normal)
    sf::Vector2f offset;  // Current offset for parallax scrolling
    float wrapWidth;      // Width at which to wrap
    
    BackgroundLayer(sf::Texture* texture, float speed = 0.0f)
        : parallaxSpeed(speed), offset(0.f, 0.f), wrapWidth(0.f)
    {
        if (texture)
        {
            sprite = std::make_unique<sf::Sprite>(*texture);
            // Create a clone for seamless wrapping
            if (speed > 0.0f)
            {
                spriteClone = std::make_unique<sf::Sprite>(*texture);
            }
            wrapWidth = static_cast<float>(texture->getSize().x);
        }
    }
    
    // Move constructor
    BackgroundLayer(BackgroundLayer&& other) noexcept = default;
    BackgroundLayer& operator=(BackgroundLayer&& other) noexcept = default;
    
    // Delete copy
    BackgroundLayer(const BackgroundLayer&) = delete;
    BackgroundLayer& operator=(const BackgroundLayer&) = delete;
};

// Manages a complete multi-layered background
class Background
{
public:
    enum class Type
    {
        Nature1,  // Sunny meadow
        Nature2,  // Night mountains
        Nature3   // Rocky hills
    };
    
    Background(Type type, class AssetManager* assetMgr, sf::Vector2u windowSize);
    
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    
    // Apply emotional color tinting
    void setEmotionTint(const sf::Color& tint);
    void resetTint();
    
    // Control parallax animation
    void setParallaxEnabled(bool enabled) { parallaxEnabled = enabled; }
    void setParallaxDirection(float x, float y) { parallaxDir = {x, y}; }
    
private:
    void setupNature1(class AssetManager* assetMgr, sf::Vector2u windowSize);
    void setupNature2(class AssetManager* assetMgr, sf::Vector2u windowSize);
    void setupNature3(class AssetManager* assetMgr, sf::Vector2u windowSize);
    
    std::vector<BackgroundLayer> layers;
    Type backgroundType;
    bool parallaxEnabled;
    sf::Vector2f parallaxDir;
    sf::Color emotionTint;
    sf::Vector2u windowSize;
};
