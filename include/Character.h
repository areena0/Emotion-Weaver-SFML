#pragma once
#include "AnimatedSprite.h"
#include "AssetManager.h"
#include <string>

// Character types in the game
enum class CharacterType
{
    Fighter,
    Samurai,
    Shinobi
};

// Helper class to create fully-animated characters
class Character
{
public:
    Character(CharacterType type, AssetManager* assetMgr);
    
    // Animation control
    void playAnimation(const std::string& animName, bool restart = false);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    
    // Transform controls
    void setPosition(const sf::Vector2f& pos) { animSprite.setPosition(pos); }
    void setScale(const sf::Vector2f& scale) { animSprite.setScale(scale); }
    void setColor(const sf::Color& color) { animSprite.setColor(color); }
    
    sf::Vector2f getPosition() const { return animSprite.getPosition(); }
    
    // Animation state
    bool isAnimationFinished() const { return animSprite.hasFinished(); }
    std::string getCurrentAnimation() const { return animSprite.getCurrentAnimation(); }
    
private:
    void setupFighterAnimations(AssetManager* assetMgr);
    void setupSamuraiAnimations(AssetManager* assetMgr);
    void setupShinobiAnimations(AssetManager* assetMgr);
    
    CharacterType type;
    AnimatedSprite animSprite;
};
