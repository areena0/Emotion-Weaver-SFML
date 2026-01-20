#pragma once
#include "DialogueSystem.h"
#include "EmotionSystem.h"
#include "Character.h"
#include "Background.h"
#include <vector>
#include <memory>

// NPC in the scenario
struct NPC
{
    std::string name;
    Character* character;
    sf::Vector2f position;
    std::vector<DialogueNode> dialogues;
    int currentDialogueIndex;
    bool hasBeenTalkedTo;
    
    NPC(const std::string& n, Character* c, const sf::Vector2f& pos)
        : name(n), character(c), position(pos), currentDialogueIndex(0), hasBeenTalkedTo(false)
    {
        if (character)
            character->setPosition(pos);
    }
    
    DialogueNode* getNextDialogue()
    {
        if (currentDialogueIndex < dialogues.size())
            return &dialogues[currentDialogueIndex];
        return nullptr;
    }
    
    void advanceDialogue()
    {
        currentDialogueIndex++;
        hasBeenTalkedTo = true;
    }
    
    bool hasMoreDialogue() const
    {
        return currentDialogueIndex < dialogues.size();
    }
};

// A complete scenario
class Scenario
{
public:
    Scenario(const std::string& name, Background::Type bgType);
    
    // Setup NPCs and dialogues
    void addNPC(const std::string& name, Character* character, const sf::Vector2f& position);
    void addDialogueToNPC(size_t npcIndex, const DialogueNode& dialogue);
    
    // Get scenario info
    std::string getName() const { return scenarioName; }
    Background::Type getBackgroundType() const { return backgroundType; }
    std::vector<NPC>& getNPCs() { return npcs; }
    
    // Goal tracking
    void setGoalDescription(const std::string& desc) { goalDescription = desc; }
    std::string getGoalDescription() const { return goalDescription; }
    
    // Check if scenario is complete
    bool isComplete() const;
    
private:
    std::string scenarioName;
    Background::Type backgroundType;
    std::vector<NPC> npcs;
    std::string goalDescription;
};

// Manages scenarios and game progression
class ScenarioManager
{
public:
    ScenarioManager();
    
    // Create predefined scenarios
    void createScenarios(AssetManager* assetMgr);
    
    // Get current scenario
    Scenario* getCurrentScenario();
    int getCurrentScenarioIndex() const { return currentScenarioIndex; }
    
    // Navigate scenarios
    void nextScenario();
    void resetScenario();
    
    // Check game state
    bool hasMoreScenarios() const { return currentScenarioIndex < scenarios.size(); }
    bool allScenariosComplete() const { return currentScenarioIndex >= scenarios.size(); }
    
private:
    std::vector<std::unique_ptr<Scenario>> scenarios;
    int currentScenarioIndex;
};
