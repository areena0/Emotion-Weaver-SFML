#include "DialogueSystem.h"

DialogueSystem::DialogueSystem(sf::Vector2u winSize)
    : windowSize(winSize)
    , active(false)
    , currentDialogue(nullptr)
    , selectedChoice(-1)
    , boxColor(0, 0, 0, 220)
    , textColor(255, 255, 255, 255)
    , choiceHighlightColor(255, 255, 100, 255)
{
    try
    {
        font = sf::Font("C:/Windows/Fonts/arial.ttf");
    }
    catch (...) {}
}

void DialogueSystem::startDialogue(const DialogueNode& node)
{
    currentDialogue = &node;
    active = true;
    selectedChoice = -1;
}

void DialogueSystem::endDialogue()
{
    active = false;
    currentDialogue = nullptr;
    selectedChoice = -1;
}

void DialogueSystem::handleInput(const std::optional<sf::Event>& event)
{
    if (!active || !currentDialogue)
        return;
    
    if (!event.has_value())
        return;
        
    const auto* keyPress = event->getIf<sf::Event::KeyPressed>();
    
    if (keyPress)
    {
        // Number keys for choices
        if (keyPress->code == sf::Keyboard::Key::Num1 && currentDialogue->choices.size() >= 1)
            selectedChoice = 0;
        else if (keyPress->code == sf::Keyboard::Key::Num2 && currentDialogue->choices.size() >= 2)
            selectedChoice = 1;
        else if (keyPress->code == sf::Keyboard::Key::Num3 && currentDialogue->choices.size() >= 3)
            selectedChoice = 2;
        else if (keyPress->code == sf::Keyboard::Key::Num4 && currentDialogue->choices.size() >= 4)
            selectedChoice = 3;
    }
}

void DialogueSystem::draw(sf::RenderWindow& window)
{
    if (!active || !currentDialogue)
        return;
    
    const float boxWidth = windowSize.x * 0.85f;
    const float boxHeight = 200.f;
    const float boxX = (windowSize.x - boxWidth) / 2.f;
    const float boxY = windowSize.y - boxHeight - 30.f;
    
    // Main dialogue box
    sf::RectangleShape dialogueBox({boxWidth, boxHeight});
    dialogueBox.setPosition({boxX, boxY});
    dialogueBox.setFillColor(boxColor);
    dialogueBox.setOutlineColor(sf::Color::White);
    dialogueBox.setOutlineThickness(3.f);
    window.draw(dialogueBox);
    
    // Speaker name
    sf::Text speakerText(font);
    speakerText.setString(currentDialogue->speakerName);
    speakerText.setCharacterSize(18);
    speakerText.setFillColor(sf::Color(255, 200, 100));
    speakerText.setStyle(sf::Text::Bold);
    speakerText.setPosition({boxX + 15.f, boxY + 10.f});
    window.draw(speakerText);
    
    // Question text
    sf::Text questionText(font);
    questionText.setString(currentDialogue->question);
    questionText.setCharacterSize(16);
    questionText.setFillColor(textColor);
    questionText.setPosition({boxX + 15.f, boxY + 40.f});
    window.draw(questionText);
    
    // Choices
    float choiceY = boxY + 80.f;
    for (size_t i = 0; i < currentDialogue->choices.size(); ++i)
    {
        sf::Text choiceText(font);
        std::string choiceStr = "[" + std::to_string(i + 1) + "] " + currentDialogue->choices[i].text;
        choiceText.setString(choiceStr);
        choiceText.setCharacterSize(14);
        choiceText.setFillColor(textColor);
        choiceText.setPosition({boxX + 20.f, choiceY});
        
        // Highlight if selected
        if (static_cast<int>(i) == selectedChoice)
        {
            choiceText.setFillColor(choiceHighlightColor);
            choiceText.setStyle(sf::Text::Bold);
        }
        
        window.draw(choiceText);
        choiceY += 25.f;
    }
}
