#include "ScenarioManager.h"

// ===== Scenario Implementation =====

Scenario::Scenario(const std::string& name, Background::Type bgType)
    : scenarioName(name)
    , backgroundType(bgType)
{
}

void Scenario::addNPC(const std::string& name, Character* character, const sf::Vector2f& position)
{
    npcs.emplace_back(name, character, position);
}

void Scenario::addDialogueToNPC(size_t npcIndex, const DialogueNode& dialogue)
{
    if (npcIndex < npcs.size())
    {
        npcs[npcIndex].dialogues.push_back(dialogue);
    }
}

bool Scenario::isComplete() const
{
    // Scenario is complete when all NPCs have been talked to
    for (const auto& npc : npcs)
    {
        if (!npc.hasBeenTalkedTo)
            return false;
    }
    return true;
}

// ===== ScenarioManager Implementation =====

ScenarioManager::ScenarioManager()
    : currentScenarioIndex(0)
{
}

void ScenarioManager::createScenarios(AssetManager* assetMgr)
{
    scenarios.clear();
    
    // ===== SCENARIO 1: The Lost Child (Nature1 - Sunny Meadow) =====
    {
        auto scenario = std::make_unique<Scenario>("The Lost Child", Background::Type::Nature1);
        scenario->setGoalDescription("Help a lost child find peace and return home safely.");
        
        // Create characters for this scenario
        // Note: These are managed by the game loop, not here
        // We'll just set up the dialogue structure
        
        scenarios.push_back(std::move(scenario));
    }
    
    // ===== SCENARIO 2: The Broken Shrine (Nature2 - Night Mountains) =====
    {
        auto scenario = std::make_unique<Scenario>("The Broken Shrine", Background::Type::Nature2);
        scenario->setGoalDescription("Restore balance to an ancient shrine before dawn.");
        
        scenarios.push_back(std::move(scenario));
    }
    
    // ===== SCENARIO 3: The Final Stand (Nature3 - Rocky Hills) =====
    {
        auto scenario = std::make_unique<Scenario>("The Final Stand", Background::Type::Nature3);
        scenario->setGoalDescription("Defend your position and survive the encounter.");
        
        scenarios.push_back(std::move(scenario));
    }
    
    currentScenarioIndex = 0;
}

Scenario* ScenarioManager::getCurrentScenario()
{
    if (currentScenarioIndex < scenarios.size())
        return scenarios[currentScenarioIndex].get();
    return nullptr;
}

void ScenarioManager::nextScenario()
{
    currentScenarioIndex++;
}

void ScenarioManager::resetScenario()
{
    if (currentScenarioIndex < scenarios.size())
    {
        auto* scenario = scenarios[currentScenarioIndex].get();
        for (auto& npc : scenario->getNPCs())
        {
            npc.currentDialogueIndex = 0;
            npc.hasBeenTalkedTo = false;
        }
    }
}
