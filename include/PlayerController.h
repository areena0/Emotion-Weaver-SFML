#pragma once
#include "Character.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <optional>
#include <cmath>

// Handles player movement and controls
class PlayerController
{
public:
    PlayerController(Character* character);
    
    // Process input - takes optional event
    void handleInput(const std::optional<sf::Event>& event);
    void update(float deltaTime);
    
    // Set jump sound
    void setJumpSound(sf::SoundBuffer* jumpBuffer);
    
    // Movement properties
    void setWalkSpeed(float speed) { walkSpeed = speed; }
    void setRunSpeed(float speed) { runSpeed = speed; }
    void setJumpHeight(float height) { jumpHeight = height; }
    void setGroundY(float ground) { groundY = ground; }
    
    // Boundary control
    void setCanExitRight(bool canExit) { canExitRight = canExit; }
    
    // State queries
    bool isMoving() const { return std::abs(velocity) > 0.1f; }
    bool isRunning() const { return running; }
    bool isJumping() const { return jumping; }
    sf::Vector2f getPosition() const;
    
    // Get facing direction
    bool isFacingRight() const { return facingRight; }
    
    // Check if near another character
    bool isNearCharacter(const sf::Vector2f& otherPos, float interactDistance = 80.f) const;
    
private:
    void updateMovement(float deltaTime);
    void updateAnimation();
    
    Character* controlledCharacter;
    
    // Movement state
    bool movingLeft;
    bool movingRight;
    bool running;
    bool jumping;
    bool facingRight;
    bool canExitRight;  // Can player exit right side of screen?
    
    // Smooth movement
    float velocity;           // Current horizontal velocity
    float acceleration;       // How fast to reach max speed
    float deceleration;       // How fast to stop
    
    // Jump physics
    float jumpVelocity;
    float gravity;
    float groundY;
    
    // Movement speeds
    float walkSpeed;
    float runSpeed;
    float jumpHeight;
    
    // Audio
    sf::SoundBuffer* jumpSoundBuffer;
    std::unique_ptr<sf::Sound> jumpSoundPtr;
    
    // Double-tap detection for running
    sf::Clock doubleTapClock;
    sf::Keyboard::Key lastKey;
    bool doubleTapTriggered;
};
