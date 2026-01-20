#include <SFML/Graphics.hpp>
#include "AssetManager.h"
#include "Background.h"
#include "Character.h"
#include "EmotionSystem.h"
#include "GameUI.h"
#include "PlayerController.h"
#include "DialogueSystem.h"
#include "ScenarioManager.h"
#include "MenuSystem.h"
#include <iostream>
#include <cmath>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Emotion Weaver - Interactive Story");
    
    AssetManager assetManager;
    
    std::cout << "\n========================================" << std::endl;
    std::cout << "  EMOTION WEAVER - FATE BY FEELINGS" << std::endl;
    std::cout << "========================================\n" << std::endl;
    
    if (!assetManager.loadAllAssets())
    {
        std::cerr << "\nERROR: Failed to load assets!" << std::endl;
        std::cin.get();
        return -1;
    }
    
    std::cout << "\nAll assets loaded!\n" << std::endl;
    
    // Menu system
    MenuSystem menuSystem(window.getSize());
    
    // Game state flag to track if we need to reset
    bool needsReset = true;
    
    // Characters (will be reset when starting new game)
    Character player(CharacterType::Fighter, &assetManager);
    Character samurai(CharacterType::Samurai, &assetManager);
    Character shinobi(CharacterType::Shinobi, &assetManager);
    
    // Facing directions
    bool playerFacingRight = true;
    bool samuraiFacingRight = true;
    bool shinobiFacingRight = true;
    
    // Background
    Background background(Background::Type::Nature1, &assetManager, window.getSize());
    
    // Systems
    EmotionSystem emotionSystem;
    GameUI ui(window.getSize());
    PlayerController playerController(&player);
    DialogueSystem dialogueSystem(window.getSize());
    
    // Setup audio
    sf::Music backgroundMusic;
    bool musicLoaded = false;
    try {
        backgroundMusic.openFromFile("assets/audio/background.mp3");
        backgroundMusic.setLooping(true);  // SFML 3 uses setLooping instead of setLoop
        backgroundMusic.setVolume(50.f);
        backgroundMusic.play();
        musicLoaded = true;
        std::cout << "Background music started!" << std::endl;
    }
    catch (...) {
        std::cerr << "Failed to play background music!" << std::endl;
    }
    
    // Setup sound effects
    std::unique_ptr<sf::Sound> successSoundPtr;
    if (auto* successBuffer = assetManager.getSoundBuffer("success_sound"))
    {
        successSoundPtr = std::make_unique<sf::Sound>(*successBuffer);
        successSoundPtr->setVolume(80.f);
    }
    
    // Setup jump sound for player
    playerController.setJumpSound(assetManager.getSoundBuffer("jump_sound"));
    
    // dialogues for each 
    // NATURE 1 - Samurai
    DialogueNode nature1_samurai("Samurai", "Steel whispers of the battle to come. How shall we stand?");
    nature1_samurai.addChoice("Place our faith in the path ahead", Emotion::Hope, 15);
    nature1_samurai.addChoice("Let the weight of uncertainty linger", Emotion::Sadness, -5);
    nature1_samurai.addChoice("Meet fate with burning wrath", Emotion::Anger, -10);
    nature1_samurai.addChoice("Breathe, and steady our spirits", Emotion::Calm, 8);
    
    // NATURE 1 - Shinobi
    DialogueNode nature1_shinobi("Shinobi", "The path ahead is dangerous. How shall we proceed?");
    nature1_shinobi.addChoice("With courage and optimism", Emotion::Hope, 15);
    nature1_shinobi.addChoice("Cautiously, fearing the worst", Emotion::Sadness, -5);
    nature1_shinobi.addChoice("Strike first, ask later", Emotion::Anger, -10);
    nature1_shinobi.addChoice("With patience and wisdom", Emotion::Calm, 8);
    
    // NATURE 2 - Samurai
    DialogueNode nature2_samurai("Samurai", "The night grows cold. What shall we do?");
    nature2_samurai.addChoice("Keep faith in the dawn", Emotion::Hope, 15);
    nature2_samurai.addChoice("Mourn the fading light", Emotion::Sadness, -5);
    nature2_samurai.addChoice("Rage against the darkness", Emotion::Anger, -10);
    nature2_samurai.addChoice("Accept the night's peace", Emotion::Calm, 8);
    
    // NATURE 2 - Shinobi
    DialogueNode nature2_shinobi("Shinobi", "Ancient spirits stir. How do we respond?");
    nature2_shinobi.addChoice("Honor them with respect", Emotion::Hope, 15);
    nature2_shinobi.addChoice("Fear their power", Emotion::Sadness, -5);
    nature2_shinobi.addChoice("Challenge their authority", Emotion::Anger, -10);
    nature2_shinobi.addChoice("Meditate in their presence", Emotion::Calm, 8);
    
    // NATURE 3 - Samurai
    DialogueNode nature3_samurai("Samurai", "This is the final test. Are you ready?");
    nature3_samurai.addChoice("Face it with determination", Emotion::Hope, 15);
    nature3_samurai.addChoice("Accept whatever comes", Emotion::Sadness, -5);
    nature3_samurai.addChoice("Fight with all your might", Emotion::Anger, -10);
    nature3_samurai.addChoice("Find inner stillness", Emotion::Calm, 8);
    
    // NATURE 3 - Shinobi
    DialogueNode nature3_shinobi("Shinobi", "Your journey ends here. What have you learned?");
    nature3_shinobi.addChoice("That hope conquers all", Emotion::Hope, 15);
    nature3_shinobi.addChoice("That suffering shapes us", Emotion::Sadness, -5);
    nature3_shinobi.addChoice("That strength is everything", Emotion::Anger, -10);
    nature3_shinobi.addChoice("That balance is key", Emotion::Calm, 8);
    
    // fonts
    sf::Font font;
    try { font = sf::Font("C:/Windows/Fonts/arial.ttf"); } catch (...) {}
    
    // interaction prompt
    sf::Text interactPrompt(font);
    interactPrompt.setString("Press [X] to interact");
    interactPrompt.setCharacterSize(16);
    interactPrompt.setFillColor(sf::Color::Yellow);
    interactPrompt.setOutlineColor(sf::Color::Black);
    interactPrompt.setOutlineThickness(2.f);
    
    // speech bubbles
    sf::Text speechBubble(font);
    speechBubble.setCharacterSize(14);
    speechBubble.setFillColor(sf::Color::White);
    speechBubble.setOutlineColor(sf::Color::Black);
    speechBubble.setOutlineThickness(2.f);
    
    // exit prompt
    sf::Text exitPrompt(font);
    exitPrompt.setString("Move RIGHT to continue →");
    exitPrompt.setCharacterSize(18);
    exitPrompt.setFillColor(sf::Color::Cyan);
    exitPrompt.setOutlineColor(sf::Color::Black);
    exitPrompt.setOutlineThickness(2.f);
    exitPrompt.setPosition({250.f, 100.f});
    
    // state game
    int currentNature = 1;
    bool talkedToSamurai = false;
    bool talkedToShinobi = false;
    bool canExit = false;
    bool followingPlayer = false;
    bool gameOver = false;
    bool playerWon = false;
    
    // Game over delay timer
    sf::Clock gameOverClock;
    bool gameOverAnimationPlaying = false;
    
    // speech bubble timers
    sf::Clock speechClock;
    bool showSamuraiSpeech = false;
    bool showShinobiSpeech = false;
    sf::Clock samuraiSpeechTimer;
    sf::Clock shinobiSpeechTimer;
    
    sf::Clock clock;
    
    std::cout << "\n=== GAME LOADED ===" << std::endl;
    std::cout << "Starting at Main Menu..." << std::endl;

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        
        // Get current game state
        GameState currentGameState = menuSystem.getCurrentState();
        
        // Reset game when starting new game
        if (currentGameState == GameState::Playing && needsReset)
        {
            std::cout << "\n=== STARTING NEW GAME ===" << std::endl;
            
            // Reset everything
            currentNature = 1;
            talkedToSamurai = false;
            talkedToShinobi = false;
            canExit = false;
            followingPlayer = false;
            gameOver = false;
            playerWon = false;
            gameOverAnimationPlaying = false;
            
            // Reset positions
            player.setPosition({200.f, 500.f});
            samurai.setPosition({500.f, 500.f});
            shinobi.setPosition({650.f, 500.f});
            
            player.setScale({2.f, 2.f});
            samurai.setScale({2.f, 2.f});
            shinobi.setScale({2.f, 2.f});
            
            playerFacingRight = true;
            samuraiFacingRight = true;
            shinobiFacingRight = true;
            
            // Start with idle animations
            player.playAnimation("Idle", true);
            samurai.playAnimation("Idle", true);
            shinobi.playAnimation("Idle", true);
            
            // Reset emotion system
            emotionSystem.reset();
            
            // Reset background
            background = Background(Background::Type::Nature1, &assetManager, window.getSize());
            
            // Reset right exit permission AND ground Y
            playerController.setCanExitRight(false);
            playerController.setGroundY(500.f);  // Fix groundY!

            needsReset = false;
        }
        
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            
            // Handle menu input when not playing
            if (currentGameState != GameState::Playing)
            {
                menuSystem.handleInput(*event);
                
                // Check if state changed to playing
                if (menuSystem.getCurrentState() == GameState::Playing && currentGameState != GameState::Playing)
                {
                    needsReset = true;
                }
                
                continue;  // Skip game input when in menu
            }
            
            // Game input (only when playing)
            if (const auto* keyPress = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPress->code == sf::Keyboard::Key::Escape)
                {
                    // Return to menu
                    menuSystem.setState(GameState::MainMenu);
                    needsReset = true;
                    continue;
                }
                
                // Interaction
                if (keyPress->code == sf::Keyboard::Key::X && !dialogueSystem.isActive() && !gameOver)
                {
                    bool nearSamurai = playerController.isNearCharacter(samurai.getPosition(), 120.f);  // Increased range
                    bool nearShinobi = playerController.isNearCharacter(shinobi.getPosition(), 120.f);
                    
                    if (nearSamurai && !talkedToSamurai)
                    {
                        if (currentNature == 1)
                            dialogueSystem.startDialogue(nature1_samurai);
                        else if (currentNature == 2)
                            dialogueSystem.startDialogue(nature2_samurai);
                        else
                            dialogueSystem.startDialogue(nature3_samurai);
                        
                        std::cout << "\nStarted conversation with Samurai (Nature " << currentNature << ")..." << std::endl;
                    }
                    else if (nearShinobi && !talkedToShinobi)
                    {
                        if (currentNature == 1)
                            dialogueSystem.startDialogue(nature1_shinobi);
                        else if (currentNature == 2)
                            dialogueSystem.startDialogue(nature2_shinobi);
                        else
                            dialogueSystem.startDialogue(nature3_shinobi);
                        
                        std::cout << "\nStarted conversation with Shinobi (Nature " << currentNature << ")..." << std::endl;
                    }
                }
            }
            
            // dialogue and movement handling
            if (dialogueSystem.isActive())
            {
                dialogueSystem.handleInput(event);
            }
            else if (!gameOver)
            {
                playerController.handleInput(event);
            }
        }
        
        // checking dialogue choices
        if (dialogueSystem.hasSelectedChoice())
        {
            int choiceIndex = dialogueSystem.getSelectedChoice();
            const DialogueNode* current = dialogueSystem.getCurrentDialogue();
            
            if (current && choiceIndex < current->choices.size())
            {
                const DialogueChoice& choice = current->choices[choiceIndex];
                
                emotionSystem.applyEmotion(choice.emotion);
                background.setEmotionTint(emotionSystem.getEmotionColor());
                
                std::cout << "\nChoice: " << choice.text << std::endl;
                std::cout << "Emotion: " << emotionSystem.getEmotionName() << std::endl;
                std::cout << "Fate: " << emotionSystem.getFate() 
                          << " | Mood: " << emotionSystem.getMoodDescription() << std::endl;
                
                if (current->speakerName == "Samurai")
                {
                    talkedToSamurai = true;
                    samurai.playAnimation("Idle", true);
                }
                else if (current->speakerName == "Shinobi")
                {
                    talkedToShinobi = true;
                    shinobi.playAnimation("Idle", true);
                }
                
                if (talkedToSamurai && talkedToShinobi)
                {
                    canExit = true;
                    followingPlayer = true;
                    speechClock.restart();
                    
                    // Allow player to exit right side
                    playerController.setCanExitRight(true);
                    
                    std::cout << "\n✓ Completed conversations in Nature " << currentNature << "!" << std::endl;
                    
                    if (currentNature == 3)
                    {
                        gameOver = true;
                        gameOverAnimationPlaying = true;
                        gameOverClock.restart();
                        
                        if (emotionSystem.isGoodEnding())
                        {
                            playerWon = true;
                            std::cout << "\n=== VICTORY ===" << std::endl;
                            std::cout << "✓ You have won! You are free to leave." << std::endl;
                            std::cout << "Showing victory animation for 5 seconds..." << std::endl;
                            player.playAnimation("Idle", true);
                            followingPlayer = false;
                            
                            // Play success sound ONLY on victory
                            if (successSoundPtr)
                            {
                                successSoundPtr->play();
                                std::cout << "Playing victory sound!" << std::endl;
                            }
                        }
                        else
                        {
                            playerWon = false;
                            std::cout << "\n=== DEFEAT ===" << std::endl;
                            std::cout << "✗ Your fate was sealed..." << std::endl;
                            std::cout << "Showing death animation for 5 seconds..." << std::endl;
                            player.playAnimation("Dead", true);
                            samurai.playAnimation("Attack_1", true);
                            shinobi.playAnimation("Attack_1", true);
                            // NO success sound on defeat
                        }
                    }
                    else
                    {
                        // Nature 1 or 2 completed - play success sound
                        if (successSoundPtr)
                        {
                            successSoundPtr->play();
                            std::cout << "Playing success sound for Nature " << currentNature << " completion!" << std::endl;
                        }
                    }
                }
                
                dialogueSystem.endDialogue();
            }
        }
        
        // updating
        if (!gameOver)
        {
            if (!dialogueSystem.isActive())
            {
                playerController.update(deltaTime);
            }
            
            // character follows other character
            if (followingPlayer && !dialogueSystem.isActive())
            {
                sf::Vector2f playerPos = playerController.getPosition();
                sf::Vector2f samuraiPos = samurai.getPosition();
                sf::Vector2f shinobiPos = shinobi.getPosition();
                
                float followSpeed = 100.f;
				float samuraiTargetDistance = 150.f;  // space between player and samurai
                float shinobiTargetDistance = 250.f;
                
                // following logic
                float samuraiDist = std::abs(playerPos.x - samuraiPos.x);
                float shinobiDist = std::abs(playerPos.x - shinobiPos.x);
                
                // samurai follows
                if (samuraiDist > samuraiTargetDistance + 20.f)
                {
                    if (playerPos.x > samuraiPos.x)
                    {
                        samuraiPos.x += followSpeed * deltaTime;
                        samurai.playAnimation("Walk", true);
                        if (!samuraiFacingRight) {
                            samurai.setScale({2.f, 2.f});
                            samuraiFacingRight = true;
                        }
                    }
                    else
                    {
                        samuraiPos.x -= followSpeed * deltaTime;
                        samurai.playAnimation("Walk", true);
                        if (samuraiFacingRight) {
                            samurai.setScale({-2.f, 2.f});
                            samuraiFacingRight = false;
                        }
                    }
                }
                else if (samuraiDist < samuraiTargetDistance - 20.f)
                {
                    if (playerPos.x < samuraiPos.x)
                    {
                        samuraiPos.x -= followSpeed * 0.5f * deltaTime;
                        samurai.playAnimation("Walk", true);
                        if (samuraiFacingRight) {
                            samurai.setScale({-2.f, 2.f});
                            samuraiFacingRight = false;
                        }
                    }
                    else
                    {
                        samuraiPos.x += followSpeed * 0.5f * deltaTime;
                        samurai.playAnimation("Walk", true);
                        if (!samuraiFacingRight) {
                            samurai.setScale({2.f, 2.f});
                            samuraiFacingRight = true;
                        }
                    }
                }
                else
                {
                    samurai.playAnimation("Idle", true);
                }
                
                // shinobi follows
                if (shinobiDist > shinobiTargetDistance + 20.f)
                {
                    if (playerPos.x > shinobiPos.x)
                    {
                        shinobiPos.x += followSpeed * deltaTime;
                        shinobi.playAnimation("Walk", true);
                        if (!shinobiFacingRight) {
                            shinobi.setScale({2.f, 2.f});
                            shinobiFacingRight = true;
                        }
                    }
                    else
                    {
                        shinobiPos.x -= followSpeed * deltaTime;
                        shinobi.playAnimation("Walk", true);
                        if (shinobiFacingRight) {
                            shinobi.setScale({-2.f, 2.f});
                            shinobiFacingRight = false;
                        }
                    }
                }
                else if (shinobiDist < shinobiTargetDistance - 20.f)
                {
                    if (playerPos.x < shinobiPos.x)
                    {
                        shinobiPos.x -= followSpeed * 0.5f * deltaTime;
                        shinobi.playAnimation("Walk", true);
                        if (shinobiFacingRight) {
                            shinobi.setScale({-2.f, 2.f});
                            shinobiFacingRight = false;
                        }
                    }
                    else
                    {
                        shinobiPos.x += followSpeed * 0.5f * deltaTime;
                        shinobi.playAnimation("Walk", true);
                        if (!shinobiFacingRight) {
                            shinobi.setScale({2.f, 2.f});
                            shinobiFacingRight = true;
                        }
                    }
                }
                else
                {
                    shinobi.playAnimation("Idle", true);
                }
                
                samurai.setPosition(samuraiPos);
                shinobi.setPosition(shinobiPos);
                
                // speech bubbles/ 5 sec
                if (speechClock.getElapsedTime().asSeconds() >= 5.f)
                {
                    showSamuraiSpeech = true;
                    showShinobiSpeech = true;
                    samuraiSpeechTimer.restart();
                    shinobiSpeechTimer.restart();
                    speechClock.restart();
                }
                
                if (showSamuraiSpeech && samuraiSpeechTimer.getElapsedTime().asSeconds() > 3.f)
                    showSamuraiSpeech = false;
                if (showShinobiSpeech && shinobiSpeechTimer.getElapsedTime().asSeconds() > 3.f)
                    showShinobiSpeech = false;
            }
            
            // transition screen
            if (canExit && playerController.getPosition().x > 820.f)  // Slightly past screen
            {
                // move NPCs off screen if following player
                if (followingPlayer)
                {
                    sf::Vector2f samuraiPos = samurai.getPosition();
                    sf::Vector2f shinobiPos = shinobi.getPosition();
                    
                    // move to the right exit
                    samuraiPos.x += 150.f * deltaTime;
                    shinobiPos.x += 150.f * deltaTime;
                    
                    samurai.setPosition(samuraiPos);
                    shinobi.setPosition(shinobiPos);
                    samurai.playAnimation("Walk", true);
                    shinobi.playAnimation("Walk", true);
                    
                    // once both are off screen, transition
                    if (samuraiPos.x > 850.f && shinobiPos.x > 850.f)
                    {
                        currentNature++;
                        std::cout << "\n→ Moving to Nature " << currentNature << "..." << std::endl;
                        
                        // Reset positions 
                        player.setPosition({100.f, 500.f});  // to 500
                        samurai.setPosition({500.f, 500.f});  // to 500
                        shinobi.setPosition({650.f, 500.f});  // to 500
                        
                        // flag reset
                        talkedToSamurai = false;
                        talkedToShinobi = false;
                        canExit = false;
                        followingPlayer = false;
                        showSamuraiSpeech = false;
                        showShinobiSpeech = false;
                        
                        // Disable right exit for new level
                        playerController.setCanExitRight(false);
                        playerController.setGroundY(500.f);  // Ensure ground stays at 500

                        // background change
                        if (currentNature == 2)
                        {
                            background = Background(Background::Type::Nature2, &assetManager, window.getSize());
                        }
                        else if (currentNature == 3)
                        {
                            background = Background(Background::Type::Nature3, &assetManager, window.getSize());
                        }
                    }
                }
            }
        }
        else
        {
            // Game over animation playing - check if 5 seconds passed
            if (gameOverAnimationPlaying && gameOverClock.getElapsedTime().asSeconds() >= 5.f)
            {
                gameOverAnimationPlaying = false;
                
                // Now show game over screen
                if (playerWon)
                {
                    menuSystem.setGameOverMessage("You escaped to freedom! Final Fate: " + 
                        std::to_string(emotionSystem.getFate()), true);
                }
                else
                {
                    menuSystem.setGameOverMessage("Your fate was sealed... Final Fate: " + 
                        std::to_string(emotionSystem.getFate()), false);
                }
                menuSystem.setState(GameState::GameOver);
                needsReset = true;
                
                std::cout << "\nShowing game over screen..." << std::endl;
            }
            
            // Game over - only winner can exit after animation
            if (playerWon && !gameOverAnimationPlaying && playerController.getPosition().x > 850.f)
            {
                std::cout << "\n🎊 GAME COMPLETE! Returning to menu..." << std::endl;
                menuSystem.setGameOverMessage("You escaped to freedom! Final Fate: " + 
                    std::to_string(emotionSystem.getFate()), true);
                menuSystem.setState(GameState::GameOver);
                needsReset = true;
            }
        }
        
        // Only update and draw game when in Playing state
        if (currentGameState == GameState::Playing)
        {
            background.update(deltaTime);
            player.update(deltaTime);
            samurai.update(deltaTime);
            shinobi.update(deltaTime);
        }
        
        // Draw
        window.clear(sf::Color::Black);
        
        // Draw based on game state
        if (currentGameState == GameState::Playing)
        {
            // Draw game
            background.draw(window);
            player.draw(window);
            samurai.draw(window);
            shinobi.draw(window);
            
            // Draw interact prompts - INCREASED RANGE
            if (!dialogueSystem.isActive() && !gameOver && !followingPlayer)
            {
                bool nearSamurai = playerController.isNearCharacter(samurai.getPosition(), 120.f);
                bool nearShinobi = playerController.isNearCharacter(shinobi.getPosition(), 120.f);
                
                if (nearSamurai && !talkedToSamurai)
                {
                    interactPrompt.setPosition({samurai.getPosition().x - 60.f, samurai.getPosition().y - 120.f});
                    window.draw(interactPrompt);
                }
                else if (nearShinobi && !talkedToShinobi)
                {
                    interactPrompt.setPosition({shinobi.getPosition().x - 60.f, shinobi.getPosition().y - 120.f});
                    window.draw(interactPrompt);
                }
            }
            
            // Draw exit prompt
            if (canExit && !gameOver)
            {
                window.draw(exitPrompt);
            }
            
            // Draw speech bubbles
            if (followingPlayer && !gameOver)
            {
                if (showSamuraiSpeech)
                {
                    speechBubble.setString("Let's go further!");
                    speechBubble.setPosition({samurai.getPosition().x - 50.f, samurai.getPosition().y - 130.f});
                    
                    sf::RectangleShape bubble({140.f, 30.f});
                    bubble.setPosition({samurai.getPosition().x - 55.f, samurai.getPosition().y - 135.f});
                    bubble.setFillColor(sf::Color(0, 0, 0, 180));
                    bubble.setOutlineColor(sf::Color::White);
                    bubble.setOutlineThickness(1.f);
                    window.draw(bubble);
                    window.draw(speechBubble);
                }
                
                if (showShinobiSpeech)
                {
                    speechBubble.setString("Let's go further!");
                    speechBubble.setPosition({shinobi.getPosition().x - 50.f, shinobi.getPosition().y - 130.f});
                    
                    sf::RectangleShape bubble({140.f, 30.f});
                    bubble.setPosition({shinobi.getPosition().x - 55.f, shinobi.getPosition().y - 135.f});
                    bubble.setFillColor(sf::Color(0, 0, 0, 180));
                    bubble.setOutlineColor(sf::Color::White);
                    bubble.setOutlineThickness(1.f);
                    window.draw(bubble);
                    window.draw(speechBubble);
                }
            }
            
            // Game over speech bubbles
            if (gameOver && playerWon)
            {
                speechBubble.setString("You have won! Go, you are free!");
                
                speechBubble.setPosition({samurai.getPosition().x - 80.f, samurai.getPosition().y - 130.f});
                sf::RectangleShape bubble1({220.f, 30.f});
                bubble1.setPosition({samurai.getPosition().x - 85.f, samurai.getPosition().y - 135.f});
                bubble1.setFillColor(sf::Color(0, 100, 0, 200));
                bubble1.setOutlineColor(sf::Color::Green);
                bubble1.setOutlineThickness(2.f);
                window.draw(bubble1);
                window.draw(speechBubble);
                
                speechBubble.setPosition({shinobi.getPosition().x - 80.f, shinobi.getPosition().y - 130.f});
                sf::RectangleShape bubble2({220.f, 30.f});
                bubble2.setPosition({shinobi.getPosition().x - 85.f, shinobi.getPosition().y - 135.f});
                bubble2.setFillColor(sf::Color(0, 100, 0, 200));
                bubble2.setOutlineColor(sf::Color::Green);
                bubble2.setOutlineThickness(2.f);
                window.draw(bubble2);
                window.draw(speechBubble);
            }

            // Draw UI
            ui.drawFateMeter(window, emotionSystem);
            ui.drawEmotionInfo(window, emotionSystem);
            dialogueSystem.draw(window);
        }
        else
        {
            // Draw menu system (Main Menu, Instructions, or Game Over)
            menuSystem.draw(window);
        }
        
        window.display();
    }
    
    std::cout << "\nGame Closed!\n" << std::endl;
    return 0;
}
