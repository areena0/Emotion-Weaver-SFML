#pragma once
#include <SFML/Graphics.hpp>
#include <string>

// The four core emotions in the game
enum class Emotion
{
    Hope,
    Sadness,
    Anger,
    Calm
};

// Represents the current emotional state and fate
class EmotionSystem
{
public:
    EmotionSystem();
    
    // Apply an emotion choice and update fate
    void applyEmotion(Emotion emotion);
    
    // Reset to initial state
    void reset();
    
    // Getters
    int getFate() const { return fate; }
    Emotion getCurrentEmotion() const { return currentEmotion; }
    std::string getEmotionName() const;
    std::string getMoodDescription() const;
    sf::Color getEmotionColor() const;
    
    // Fate analysis
    bool isGoodEnding() const { return fate >= 40; }
    bool isNeutralEnding() const { return fate >= -10 && fate < 40; }
    bool isBadEnding() const { return fate < -10; }
    std::string getEndingType() const;
    
    // Get fate change for an emotion (for preview/UI)
    int getFateChange(Emotion emotion) const;
    
private:
    int fate;  // Range: -100 to +100
    Emotion currentEmotion;
    
    // Emotion impact on fate
    int calculateFateChange(Emotion emotion) const;
    void clampFate();
};
