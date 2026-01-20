#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

// Game states
enum class GameState
{
    MainMenu,
    Instructions,
    Playing,
    GameOver
};

// Menu system manager
class MenuSystem
{
public:
    MenuSystem(sf::Vector2u windowSize);
    
    // Handle input for menus
    void handleInput(const sf::Event& event);
    
    // Draw current menu
    void draw(sf::RenderWindow& window);
    
    // State management
    GameState getCurrentState() const { return currentState; }
    void setState(GameState state);
    
    // Game over specific
    void setGameOverMessage(const std::string& message, bool won);
    
private:
    void drawMainMenu(sf::RenderWindow& window);
    void drawInstructions(sf::RenderWindow& window);
    void drawGameOver(sf::RenderWindow& window);
    
    sf::Vector2u windowSize;
    sf::Font font;
    GameState currentState;
    
    // Main menu
    int selectedMenuItem;
    std::vector<std::string> menuItems;
    
    // Game over
    std::string gameOverMessage;
    bool playerWon;
    
    // Colors
    sf::Color titleColor;
    sf::Color selectedColor;
    sf::Color normalColor;
    sf::Color backgroundColor;
};
