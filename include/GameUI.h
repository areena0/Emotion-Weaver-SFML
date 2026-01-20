#pragma once
#include <SFML/Graphics.hpp>
#include "EmotionSystem.h"
#include <string>
#include <memory>

// UI overlay for displaying game state
class GameUI
{
public:
    GameUI(sf::Vector2u windowSize);
    
    // Update UI with current emotion system state
    void update(const EmotionSystem& emotionSystem);
    
    // Draw UI elements (public so they can be called from main)
    void draw(sf::RenderWindow& window);
    void drawFateMeter(sf::RenderWindow& window, const EmotionSystem& emotionSystem);
    void drawEmotionInfo(sf::RenderWindow& window, const EmotionSystem& emotionSystem);
    void drawInstructions(sf::RenderWindow& window);
    void drawTextBox(sf::RenderWindow& window);
    
    // Show/hide different UI elements
    void setShowFateMeter(bool show) { showFateMeter = show; }
    void setShowEmotionInfo(bool show) { showEmotionInfo = show; }
    void setShowInstructions(bool show) { showInstructions = show; }
    
    // Display custom text box (for narrative)
    void showTextBox(const std::string& text);
    void hideTextBox();
    
private:
    sf::Vector2u windowSize;
    sf::Font font;
    
    bool showFateMeter;
    bool showEmotionInfo;
    bool showInstructions;
    bool textBoxVisible;
    std::string textBoxContent;
    
    // UI colors
    sf::Color uiBackgroundColor;
    sf::Color uiTextColor;
    sf::Color fateMeterGoodColor;
    sf::Color fateMeterBadColor;
    sf::Color fateMeterNeutralColor;
};
