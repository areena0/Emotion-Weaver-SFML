#include "Character.h"

Character::Character(CharacterType charType, AssetManager* assetMgr)
    : type(charType)
{
    switch (type)
    {
    case CharacterType::Fighter:
        setupFighterAnimations(assetMgr);
        break;
    case CharacterType::Samurai:
        setupSamuraiAnimations(assetMgr);
        break;
    case CharacterType::Shinobi:
        setupShinobiAnimations(assetMgr);
        break;
    }
    
    // Default to idle animation
    animSprite.play("Idle");
}

void Character::setupFighterAnimations(AssetManager* assetMgr)
{
    // Fighter frame counts (from spec)
    animSprite.addAnimation("Attack_1", Animation(assetMgr->getTexture("fighter_attack1"), 4, 0.1f, false));
    animSprite.addAnimation("Attack_2", Animation(assetMgr->getTexture("fighter_attack2"), 3, 0.1f, false));
    animSprite.addAnimation("Attack_3", Animation(assetMgr->getTexture("fighter_attack3"), 4, 0.1f, false));
    animSprite.addAnimation("Dead", Animation(assetMgr->getTexture("fighter_dead"), 3, 0.15f, false));
    animSprite.addAnimation("Hurt", Animation(assetMgr->getTexture("fighter_hurt"), 3, 0.1f, false));
    animSprite.addAnimation("Idle", Animation(assetMgr->getTexture("fighter_idle"), 6, 0.15f, true));
    animSprite.addAnimation("Jump", Animation(assetMgr->getTexture("fighter_jump"), 10, 0.08f, false));
    animSprite.addAnimation("Run", Animation(assetMgr->getTexture("fighter_run"), 8, 0.1f, true));
    animSprite.addAnimation("Shield", Animation(assetMgr->getTexture("fighter_shield"), 2, 0.2f, true));
    animSprite.addAnimation("Walk", Animation(assetMgr->getTexture("fighter_walk"), 8, 0.12f, true));
}

void Character::setupSamuraiAnimations(AssetManager* assetMgr)
{
    // Samurai frame counts (from spec)
    animSprite.addAnimation("Attack_1", Animation(assetMgr->getTexture("samurai_attack1"), 6, 0.1f, false));
    animSprite.addAnimation("Attack_2", Animation(assetMgr->getTexture("samurai_attack2"), 4, 0.1f, false));
    animSprite.addAnimation("Attack_3", Animation(assetMgr->getTexture("samurai_attack3"), 3, 0.1f, false));
    animSprite.addAnimation("Dead", Animation(assetMgr->getTexture("samurai_dead"), 3, 0.15f, false));
    animSprite.addAnimation("Hurt", Animation(assetMgr->getTexture("samurai_hurt"), 2, 0.1f, false));
    animSprite.addAnimation("Idle", Animation(assetMgr->getTexture("samurai_idle"), 6, 0.15f, true));
    animSprite.addAnimation("Jump", Animation(assetMgr->getTexture("samurai_jump"), 12, 0.08f, false));
    animSprite.addAnimation("Run", Animation(assetMgr->getTexture("samurai_run"), 8, 0.1f, true));
    animSprite.addAnimation("Shield", Animation(assetMgr->getTexture("samurai_shield"), 2, 0.2f, true));
    animSprite.addAnimation("Walk", Animation(assetMgr->getTexture("samurai_walk"), 8, 0.12f, true));
}

void Character::setupShinobiAnimations(AssetManager* assetMgr)
{
    // Shinobi frame counts (from spec)
    animSprite.addAnimation("Attack_1", Animation(assetMgr->getTexture("shinobi_attack1"), 5, 0.1f, false));
    animSprite.addAnimation("Attack_2", Animation(assetMgr->getTexture("shinobi_attack2"), 3, 0.1f, false));
    animSprite.addAnimation("Attack_3", Animation(assetMgr->getTexture("shinobi_attack3"), 4, 0.1f, false));
    animSprite.addAnimation("Dead", Animation(assetMgr->getTexture("shinobi_dead"), 4, 0.15f, false));
    animSprite.addAnimation("Hurt", Animation(assetMgr->getTexture("shinobi_hurt"), 2, 0.1f, false));
    animSprite.addAnimation("Idle", Animation(assetMgr->getTexture("shinobi_idle"), 6, 0.15f, true));
    animSprite.addAnimation("Jump", Animation(assetMgr->getTexture("shinobi_jump"), 12, 0.08f, false));
    animSprite.addAnimation("Run", Animation(assetMgr->getTexture("shinobi_run"), 8, 0.1f, true));
    animSprite.addAnimation("Shield", Animation(assetMgr->getTexture("shinobi_shield"), 4, 0.2f, true));
    animSprite.addAnimation("Walk", Animation(assetMgr->getTexture("shinobi_walk"), 8, 0.12f, true));
}

void Character::playAnimation(const std::string& animName, bool restart)
{
    animSprite.play(animName, restart);
}

void Character::update(float deltaTime)
{
    animSprite.update(deltaTime);
}

void Character::draw(sf::RenderWindow& window)
{
    animSprite.draw(window);
}
