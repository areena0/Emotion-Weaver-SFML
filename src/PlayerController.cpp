#include "PlayerController.h"
#include <cmath>

PlayerController::PlayerController(Character* character)
    : controlledCharacter(character)
    , movingLeft(false)
    , movingRight(false)
    , running(false)
    , jumping(false)
    , facingRight(true)
    , canExitRight(false)
    , velocity(0.f)
    , acceleration(800.f)
    , deceleration(1200.f)
    , jumpVelocity(0.f)
    , gravity(1200.f)      // Increased gravity for faster fall
    , groundY(500.f)
    , walkSpeed(150.f)
    , runSpeed(250.f)
    , jumpHeight(240.f)    // Increased from 180 to 240 for higher jump
    , jumpSoundBuffer(nullptr)
    , lastKey(sf::Keyboard::Key::Unknown)
    , doubleTapTriggered(false)
{
    if (controlledCharacter)
    {
        groundY = controlledCharacter->getPosition().y;
    }
}

void PlayerController::handleInput(const std::optional<sf::Event>& event)
{
    if (!event.has_value())
        return;
        
    const auto* keyPress = event->getIf<sf::Event::KeyPressed>();
    const auto* keyRelease = event->getIf<sf::Event::KeyReleased>();
    
    if (keyPress)
    {
        // Check for double-tap to run
        if (keyPress->code == sf::Keyboard::Key::Left || keyPress->code == sf::Keyboard::Key::Right)
        {
            if (doubleTapClock.getElapsedTime().asSeconds() < 0.3f && keyPress->code == lastKey)
            {
                running = true;
            }
            doubleTapClock.restart();
            lastKey = keyPress->code;
        }
        
        // Left key pressed
        if (keyPress->code == sf::Keyboard::Key::Left)
        {
            // If currently moving/facing right, just turn (don't start moving yet)
            if (facingRight)
            {
                facingRight = false;
                movingLeft = false;  // Don't move, just turn
                movingRight = false;
            }
            else
            {
                // Already facing left, start moving
                movingLeft = true;
                movingRight = false;
            }
        }
        
        // Right key pressed
        if (keyPress->code == sf::Keyboard::Key::Right)
        {
            // If currently moving/facing left, just turn (don't start moving yet)
            if (!facingRight)
            {
                facingRight = true;
                movingRight = false;  // Don't move, just turn
                movingLeft = false;
            }
            else
            {
                // Already facing right, start moving
                movingRight = true;
                movingLeft = false;
            }
        }
            
        // Jump - Changed to P key
        if (keyPress->code == sf::Keyboard::Key::P && !jumping)
        {
            jumping = true;
            jumpVelocity = -jumpHeight;
            
            // Play jump sound
            if (jumpSoundPtr)
            {
                jumpSoundPtr->play();
            }
        }
    }
    
    if (keyRelease)
    {
        if (keyRelease->code == sf::Keyboard::Key::Left)
        {
            movingLeft = false;
            running = false;
        }
        if (keyRelease->code == sf::Keyboard::Key::Right)
        {
            movingRight = false;
            running = false;
        }
    }
}

void PlayerController::update(float deltaTime)
{
    updateMovement(deltaTime);
    updateAnimation();
}

void PlayerController::updateMovement(float deltaTime)
{
    if (!controlledCharacter)
        return;
    
    sf::Vector2f pos = controlledCharacter->getPosition();
    float speed = running ? runSpeed : walkSpeed;
    
    // Simple direct movement - no velocity system
    if (movingLeft)
    {
        pos.x -= speed * deltaTime;
    }
    else if (movingRight)
    {
        pos.x += speed * deltaTime;
    }
    
    // Clamp to screen bounds
    // Left boundary - keep character visible (at least 30px from edge)
    pos.x = std::max(30.f, pos.x);
    
    // Right boundary - only enforce if level isn't complete
    if (!canExitRight)
    {
        pos.x = std::min(770.f, pos.x);
    }
    
    // Jump physics
    if (jumping)
    {
        jumpVelocity += gravity * deltaTime;
        pos.y += jumpVelocity * deltaTime;
        
        // Land on ground
        if (pos.y >= groundY)
        {
            pos.y = groundY;
            jumping = false;
            jumpVelocity = 0.f;
        }
    }
    
    controlledCharacter->setPosition(pos);
    
    // Update sprite facing
    if (facingRight)
        controlledCharacter->setScale({2.f, 2.f});
    else
        controlledCharacter->setScale({-2.f, 2.f});
}

void PlayerController::updateAnimation()
{
    if (!controlledCharacter)
        return;
    
    // Priority: Jump > Run > Walk > Idle
    if (jumping)
    {
        if (controlledCharacter->getCurrentAnimation() != "Jump")
            controlledCharacter->playAnimation("Jump", false);
    }
    else if (running && (movingLeft || movingRight))
    {
        if (controlledCharacter->getCurrentAnimation() != "Run")
            controlledCharacter->playAnimation("Run", true);
    }
    else if (movingLeft || movingRight)
    {
        if (controlledCharacter->getCurrentAnimation() != "Walk")
            controlledCharacter->playAnimation("Walk", true);
    }
    else
    {
        if (controlledCharacter->getCurrentAnimation() != "Idle")
            controlledCharacter->playAnimation("Idle", true);
    }
}

sf::Vector2f PlayerController::getPosition() const
{
    if (controlledCharacter)
        return controlledCharacter->getPosition();
    return sf::Vector2f(0.f, 0.f);
}

bool PlayerController::isNearCharacter(const sf::Vector2f& otherPos, float interactDistance) const
{
    sf::Vector2f myPos = getPosition();
    float distance = std::sqrt(std::pow(otherPos.x - myPos.x, 2) + std::pow(otherPos.y - myPos.y, 2));
    return distance < interactDistance;
}

void PlayerController::setJumpSound(sf::SoundBuffer* jumpBuffer)
{
    jumpSoundBuffer = jumpBuffer;
    if (jumpSoundBuffer)
    {
        jumpSoundPtr = std::make_unique<sf::Sound>(*jumpSoundBuffer);
        jumpSoundPtr->setVolume(70.f);
    }
}
