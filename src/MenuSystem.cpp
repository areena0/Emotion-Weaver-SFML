#include "MenuSystem.h"

MenuSystem::MenuSystem(sf::Vector2u winSize)
    : windowSize(winSize)
    , currentState(GameState::MainMenu)
    , selectedMenuItem(0)
    , playerWon(false)
    , titleColor(255, 215, 0)      // Gold
    , selectedColor(255, 255, 100)  // Bright yellow
    , normalColor(200, 200, 200)    // Light gray
    , backgroundColor(20, 20, 30)   // Dark blue-gray
{
    // Load font
    try
    {
        font = sf::Font("C:/Windows/Fonts/arial.ttf");
    }
    catch (...) {}
    
    // Setup main menu items
    menuItems.push_back("Start Game");
    menuItems.push_back("Instructions");
}

void MenuSystem::setState(GameState state)
{
    currentState = state;
    selectedMenuItem = 0;  // Reset selection
}

void MenuSystem::setGameOverMessage(const std::string& message, bool won)
{
    gameOverMessage = message;
    playerWon = won;
}

void MenuSystem::handleInput(const sf::Event& event)
{
    const auto* keyPress = event.getIf<sf::Event::KeyPressed>();
    if (!keyPress)
        return;
    
    if (currentState == GameState::MainMenu)
    {
        // Navigate menu
        if (keyPress->code == sf::Keyboard::Key::Up)
        {
            selectedMenuItem--;
            if (selectedMenuItem < 0)
                selectedMenuItem = menuItems.size() - 1;
        }
        else if (keyPress->code == sf::Keyboard::Key::Down)
        {
            selectedMenuItem++;
            if (selectedMenuItem >= menuItems.size())
                selectedMenuItem = 0;
        }
        else if (keyPress->code == sf::Keyboard::Key::Enter)
        {
            // Select menu item
            if (selectedMenuItem == 0)
            {
                setState(GameState::Playing);
            }
            else if (selectedMenuItem == 1)
            {
                setState(GameState::Instructions);
            }
        }
    }
    else if (currentState == GameState::Instructions)
    {
        // Press ESC to go back
        if (keyPress->code == sf::Keyboard::Key::Escape)
        {
            setState(GameState::MainMenu);
        }
    }
    else if (currentState == GameState::GameOver)
    {
        // Press ESC to return to main menu
        if (keyPress->code == sf::Keyboard::Key::Escape)
        {
            setState(GameState::MainMenu);
        }
    }
}

void MenuSystem::draw(sf::RenderWindow& window)
{
    if (currentState == GameState::MainMenu)
    {
        drawMainMenu(window);
    }
    else if (currentState == GameState::Instructions)
    {
        drawInstructions(window);
    }
    else if (currentState == GameState::GameOver)
    {
        drawGameOver(window);
    }
}

void MenuSystem::drawMainMenu(sf::RenderWindow& window)
{
    // Background
    sf::RectangleShape background({static_cast<float>(windowSize.x), static_cast<float>(windowSize.y)});
    background.setFillColor(backgroundColor);
    window.draw(background);
    
    // Title
    sf::Text title(font);
    title.setString("EMOTION WEAVER");
    title.setCharacterSize(60);
    title.setFillColor(titleColor);
    title.setStyle(sf::Text::Bold);
    
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setPosition({windowSize.x / 2.f - titleBounds.size.x / 2.f, 100.f});
    window.draw(title);
    
    // Subtitle
    sf::Text subtitle(font);
    subtitle.setString("Fate by Feelings");
    subtitle.setCharacterSize(24);
    subtitle.setFillColor(normalColor);
    subtitle.setStyle(sf::Text::Italic);
    
    sf::FloatRect subtitleBounds = subtitle.getLocalBounds();
    subtitle.setPosition({windowSize.x / 2.f - subtitleBounds.size.x / 2.f, 180.f});
    window.draw(subtitle);
    
    // Menu items
    float startY = 300.f;
    float spacing = 60.f;
    
    for (size_t i = 0; i < menuItems.size(); ++i)
    {
        sf::Text menuText(font);
        menuText.setString(menuItems[i]);
        menuText.setCharacterSize(32);
        
        // Highlight selected item
        if (static_cast<int>(i) == selectedMenuItem)
        {
            menuText.setFillColor(selectedColor);
            menuText.setStyle(sf::Text::Bold);
            menuText.setString("> " + menuItems[i] + " <");
        }
        else
        {
            menuText.setFillColor(normalColor);
        }
        
        sf::FloatRect bounds = menuText.getLocalBounds();
        menuText.setPosition({windowSize.x / 2.f - bounds.size.x / 2.f, startY + i * spacing});
        window.draw(menuText);
    }
    
    // Controls hint
    sf::Text hint(font);
    hint.setString("Use UP/DOWN arrows and ENTER to select");
    hint.setCharacterSize(16);
    hint.setFillColor(sf::Color(150, 150, 150));
    
    sf::FloatRect hintBounds = hint.getLocalBounds();
    hint.setPosition({windowSize.x / 2.f - hintBounds.size.x / 2.f, windowSize.y - 50.f});
    window.draw(hint);
}

void MenuSystem::drawInstructions(sf::RenderWindow& window)
{
    // Background
    sf::RectangleShape background({static_cast<float>(windowSize.x), static_cast<float>(windowSize.y)});
    background.setFillColor(backgroundColor);
    window.draw(background);
    
    // Title
    sf::Text title(font);
    title.setString("INSTRUCTIONS");
    title.setCharacterSize(48);
    title.setFillColor(titleColor);
    title.setStyle(sf::Text::Bold);
    
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setPosition({windowSize.x / 2.f - titleBounds.size.x / 2.f, 30.f});
    window.draw(title);
    
    // Back instruction
    sf::Text backText(font);
    backText.setString("Press ESC to go back");
    backText.setCharacterSize(18);
    backText.setFillColor(sf::Color::Cyan);
    
    sf::FloatRect backBounds = backText.getLocalBounds();
    backText.setPosition({windowSize.x / 2.f - backBounds.size.x / 2.f, 80.f});
    window.draw(backText);
    
    // Instructions content
    std::vector<std::string> instructions = {
        "GAME OBJECTIVE:",
        "Navigate through 3 nature areas and make emotional choices",
        "that will determine your fate!",
        "",
        "MOVEMENT CONTROLS:",
        "Arrow Keys - Walk left/right",
        "Double-tap Arrow - Run",
        "P - Jump",
        "",
        "INTERACTION:",
        "[X] - Talk to NPCs when nearby",
        "[1][2][3][4] - Choose dialogue responses",
        "",
        "EMOTIONS:",
        "Hope (+15 Fate) - Optimistic, uplifting choices",
        "Calm (+8 Fate) - Peaceful, balanced choices",
        "Sadness (-5 Fate) - Reflective, sorrowful choices",
        "Anger (-10 Fate) - Aggressive, intense choices",
        "",
        "WIN CONDITION:",
        "Reach Fate >= 40 by the end of Nature 3 to win your freedom!",
        "Fate < -10 means defeat - the enemies will prevail."
    };
    
    float startY = 130.f;
    float lineHeight = 22.f;
    
    for (const auto& line : instructions)
    {
        sf::Text instructText(font);
        instructText.setString(line);
        
        // Headers in bold
        if (line.find(':') != std::string::npos && line.find('[') == std::string::npos)
        {
            instructText.setCharacterSize(18);
            instructText.setFillColor(selectedColor);
            instructText.setStyle(sf::Text::Bold);
        }
        else if (line.empty())
        {
            lineHeight = 10.f;  // Smaller gap for empty lines
        }
        else
        {
            instructText.setCharacterSize(16);
            instructText.setFillColor(normalColor);
        }
        
        instructText.setPosition({50.f, startY});
        window.draw(instructText);
        
        startY += lineHeight;
        lineHeight = 22.f;  // Reset line height
    }
}

void MenuSystem::drawGameOver(sf::RenderWindow& window)
{
    // Semi-transparent overlay
    sf::RectangleShape overlay({static_cast<float>(windowSize.x), static_cast<float>(windowSize.y)});
    overlay.setFillColor(sf::Color(0, 0, 0, 200));
    window.draw(overlay);
    
    // Game Over title
    sf::Text title(font);
    if (playerWon)
    {
        title.setString("VICTORY!");
        title.setFillColor(sf::Color::Green);
    }
    else
    {
        title.setString("DEFEAT");
        title.setFillColor(sf::Color::Red);
    }
    title.setCharacterSize(72);
    title.setStyle(sf::Text::Bold);
    
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setPosition({windowSize.x / 2.f - titleBounds.size.x / 2.f, 150.f});
    window.draw(title);
    
    // Message
    sf::Text message(font);
    message.setString(gameOverMessage);
    message.setCharacterSize(24);
    message.setFillColor(sf::Color::White);
    
    sf::FloatRect msgBounds = message.getLocalBounds();
    message.setPosition({windowSize.x / 2.f - msgBounds.size.x / 2.f, 260.f});
    window.draw(message);
    
    // Return instruction
    sf::Text returnText(font);
    returnText.setString("Press ESC to return to Main Menu");
    returnText.setCharacterSize(20);
    returnText.setFillColor(sf::Color::Cyan);
    
    sf::FloatRect returnBounds = returnText.getLocalBounds();
    returnText.setPosition({windowSize.x / 2.f - returnBounds.size.x / 2.f, 400.f});
    window.draw(returnText);
}
