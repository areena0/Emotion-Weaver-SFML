#include "EmotionSystem.h"
#include <algorithm>

EmotionSystem::EmotionSystem()
    : fate(0)
    , currentEmotion(Emotion::Calm)
{
}

void EmotionSystem::applyEmotion(Emotion emotion)
{
    currentEmotion = emotion;
    int change = calculateFateChange(emotion);
    fate += change;
    clampFate();
}

void EmotionSystem::reset()
{
    fate = 0;
    currentEmotion = Emotion::Calm;
}

std::string EmotionSystem::getEmotionName() const
{
    switch (currentEmotion)
    {
    case Emotion::Hope:    return "Hope";
    case Emotion::Sadness: return "Sadness";
    case Emotion::Anger:   return "Anger";
    case Emotion::Calm:    return "Calm";
    default:               return "Unknown";
    }
}

std::string EmotionSystem::getMoodDescription() const
{
    if (fate >= 60)
        return "Radiant";
    else if (fate >= 40)
        return "Hopeful";
    else if (fate >= 20)
        return "Positive";
    else if (fate >= -10)
        return "Neutral";
    else if (fate >= -30)
        return "Troubled";
    else if (fate >= -50)
        return "Grim";
    else
        return "Despair";
}

sf::Color EmotionSystem::getEmotionColor() const
{
    switch (currentEmotion)
    {
    case Emotion::Hope:
        return sf::Color(255, 230, 180); // Warm yellow/gold
    case Emotion::Sadness:
        return sf::Color(180, 190, 230); // Cool blue
    case Emotion::Anger:
        return sf::Color(255, 150, 150); // Intense red
    case Emotion::Calm:
        return sf::Color(200, 240, 210); // Soft green
    default:
        return sf::Color::White;
    }
}

std::string EmotionSystem::getEndingType() const
{
    if (isGoodEnding())
        return "Good Ending";
    else if (isNeutralEnding())
        return "Neutral Ending";
    else
        return "Bad Ending";
}

int EmotionSystem::getFateChange(Emotion emotion) const
{
    return calculateFateChange(emotion);
}

int EmotionSystem::calculateFateChange(Emotion emotion) const
{
    // Each emotion has a different impact on fate
    switch (emotion)
    {
    case Emotion::Hope:
        // Always positive, moderate boost
        return 15;
        
    case Emotion::Sadness:
        // Context-dependent: slight negative
        // (Can reveal truths but weakens resolve)
        return -5;
        
    case Emotion::Anger:
        // High risk/high reward: large swing
        // For now, slightly negative (can be destructive)
        return -10;
        
    case Emotion::Calm:
        // Stabilizing, small positive
        return 8;
        
    default:
        return 0;
    }
}

void EmotionSystem::clampFate()
{
    fate = std::clamp(fate, -100, 100);
}
