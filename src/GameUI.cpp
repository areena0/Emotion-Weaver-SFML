#include "GameUI.h"
#include <sstream>
#include <iomanip>

GameUI::GameUI(sf::Vector2u winSize)
    : windowSize(winSize)
    , showFateMeter(true)
    , showEmotionInfo(true)
    , showInstructions(false)
    , textBoxVisible(false)
    , uiBackgroundColor(0, 0, 0, 180)
    , uiTextColor(255, 255, 255, 255)
    , fateMeterGoodColor(100, 255, 100, 255)
    , fateMeterBadColor(255, 100, 100, 255)
    , fateMeterNeutralColor(200, 200, 200, 255)
{
    // Try to load a system font (SFML 3 will search system fonts)
    // If this fails, text will still work with default font
    try
    {
        font = sf::Font("C:/Windows/Fonts/arial.ttf");
    }
    catch (...)
    {
        // Fallback - use default font if available
    }
}

void GameUI::update(const EmotionSystem& emotionSystem)
{
    // UI updates happen in draw based on emotion system state
}

void GameUI::draw(sf::RenderWindow& window)
{
    // Note: We'll pass EmotionSystem in the individual draw functions
    // For now, this is a placeholder that can be called from main loop
}

void GameUI::drawFateMeter(sf::RenderWindow& window, const EmotionSystem& emotionSystem)
{
    if (!showFateMeter)
        return;
    
    const float barWidth = 300.f;
    const float barHeight = 30.f;
    const float barX = windowSize.x - barWidth - 20.f;
    const float barY = 20.f;
    
    // Background
    sf::RectangleShape background({barWidth, barHeight});
    background.setPosition({barX, barY});
    background.setFillColor(uiBackgroundColor);
    background.setOutlineColor(uiTextColor);
    background.setOutlineThickness(2.f);
    window.draw(background);
    
    // Fate bar
    int fate = emotionSystem.getFate();
    float fatePercent = (fate + 100.f) / 200.f; // Map -100..100 to 0..1
    float fillWidth = barWidth * fatePercent;
    
    sf::RectangleShape fateBar({fillWidth, barHeight});
    fateBar.setPosition({barX, barY});
    
    // Color based on fate value
    if (emotionSystem.isGoodEnding())
        fateBar.setFillColor(fateMeterGoodColor);
    else if (emotionSystem.isBadEnding())
        fateBar.setFillColor(fateMeterBadColor);
    else
        fateBar.setFillColor(fateMeterNeutralColor);
    
    window.draw(fateBar);
    
    // Center line (neutral point)
    sf::RectangleShape centerLine({2.f, barHeight});
    centerLine.setPosition({barX + barWidth / 2.f, barY});
    centerLine.setFillColor(sf::Color(255, 255, 255, 150));
    window.draw(centerLine);
    
    // Fate text
    sf::Text fateText(font);
    std::stringstream ss;
    ss << "Fate: " << fate;
    fateText.setString(ss.str());
    fateText.setCharacterSize(18);
    fateText.setFillColor(uiTextColor);
    fateText.setPosition({barX, barY - 25.f});
    window.draw(fateText);
}

void GameUI::drawEmotionInfo(sf::RenderWindow& window, const EmotionSystem& emotionSystem)
{
    if (!showEmotionInfo)
        return;
    
    const float infoX = 20.f;
    const float infoY = 20.f;
    
    // Emotion name
    sf::Text emotionText(font);
    emotionText.setString("Current Emotion: " + emotionSystem.getEmotionName());
    emotionText.setCharacterSize(20);
    emotionText.setFillColor(emotionSystem.getEmotionColor());
    emotionText.setPosition({infoX, infoY});
    
    // Add black outline for readability
    emotionText.setOutlineColor(sf::Color::Black);
    emotionText.setOutlineThickness(2.f);
    window.draw(emotionText);
    
    // Mood description
    sf::Text moodText(font);
    moodText.setString("Mood: " + emotionSystem.getMoodDescription());
    moodText.setCharacterSize(18);
    moodText.setFillColor(uiTextColor);
    moodText.setPosition({infoX, infoY + 30.f});
    moodText.setOutlineColor(sf::Color::Black);
    moodText.setOutlineThickness(2.f);
    window.draw(moodText);
}

void GameUI::drawInstructions(sf::RenderWindow& window)
{
    if (!showInstructions)
        return;
    
    // Make box wider and better positioned
    const float boxWidth = 450.f;  // Increased from 300
    const float boxHeight = 80.f;
    const float instructX = windowSize.x / 2.f - boxWidth / 2.f;  // Center horizontally
    const float instructY = windowSize.y - boxHeight - 20.f;
    
    // Background box
    sf::RectangleShape background({boxWidth, boxHeight});
    background.setPosition({instructX, instructY});
    background.setFillColor(uiBackgroundColor);
    background.setOutlineColor(uiTextColor);
    background.setOutlineThickness(2.f);
    window.draw(background);
    
    // Instructions text
    sf::Text instructions(font);
    instructions.setString("Choose an Emotion:\n[H] Hope  [S] Sadness  [A] Anger  [C] Calm");
    instructions.setCharacterSize(16);
    instructions.setFillColor(uiTextColor);
    instructions.setPosition({instructX + 10.f, instructY + 10.f});
    window.draw(instructions);
}

void GameUI::showTextBox(const std::string& text)
{
    textBoxContent = text;
    textBoxVisible = true;
}

void GameUI::hideTextBox()
{
    textBoxVisible = false;
}

void GameUI::drawTextBox(sf::RenderWindow& window)
{
    if (!textBoxVisible)
        return;
    
    const float boxWidth = windowSize.x * 0.8f;
    const float boxHeight = 150.f;
    const float boxX = (windowSize.x - boxWidth) / 2.f;
    const float boxY = windowSize.y - boxHeight - 20.f;
    
    // Semi-transparent background
    sf::RectangleShape background({boxWidth, boxHeight});
    background.setPosition({boxX, boxY});
    background.setFillColor(sf::Color(0, 0, 0, 200));
    background.setOutlineColor(sf::Color(255, 255, 255, 255));
    background.setOutlineThickness(3.f);
    window.draw(background);
    
    // Text content
    sf::Text text(font);
    text.setString(textBoxContent);
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::White);
    text.setPosition({boxX + 15.f, boxY + 15.f});
    window.draw(text);
}
