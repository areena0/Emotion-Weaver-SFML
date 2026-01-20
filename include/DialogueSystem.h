#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <optional>
#include "EmotionSystem.h"

// A single dialogue choice
struct DialogueChoice
{
    std::string text;
    Emotion emotion;
    int fateImpact;
    
    DialogueChoice(const std::string& txt, Emotion em, int impact)
        : text(txt), emotion(em), fateImpact(impact)
    {}
};

// A dialogue exchange (question + choices)
struct DialogueNode
{
    std::string speakerName;
    std::string question;
    std::vector<DialogueChoice> choices;
    
    DialogueNode(const std::string& speaker, const std::string& q)
        : speakerName(speaker), question(q)
    {}
    
    void addChoice(const std::string& text, Emotion emotion, int fateImpact)
    {
        choices.emplace_back(text, emotion, fateImpact);
    }
};

// Manages dialogue display and interaction
class DialogueSystem
{
public:
    DialogueSystem(sf::Vector2u windowSize);
    
    // Start a dialogue with given node
    void startDialogue(const DialogueNode& node);
    void endDialogue();
    
    // Handle input (number keys 1-4 for choices)
    void handleInput(const std::optional<sf::Event>& event);
    
    // Draw dialogue box
    void draw(sf::RenderWindow& window);
    
    // State
    bool isActive() const { return active; }
    bool hasSelectedChoice() const { return selectedChoice >= 0; }
    int getSelectedChoice() const { return selectedChoice; }
    void resetSelection() { selectedChoice = -1; }
    
    // Get current dialogue info
    const DialogueNode* getCurrentDialogue() const { return currentDialogue; }
    
private:
    sf::Vector2u windowSize;
    sf::Font font;
    
    bool active;
    const DialogueNode* currentDialogue;
    int selectedChoice;
    
    // UI colors
    sf::Color boxColor;
    sf::Color textColor;
    sf::Color choiceHighlightColor;
};
