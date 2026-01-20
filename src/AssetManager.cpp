#include "AssetManager.h"

bool AssetManager::loadTexture(const std::string& name, const std::string& filepath)
{
    try
    {
        // SFML 3 uses direct constructor
        auto texture = std::make_unique<sf::Texture>(filepath);
        std::cout << "Loaded texture: " << name << " from " << filepath << std::endl;
        textures[name] = std::move(texture);
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Failed to load texture: " << filepath << " - " << e.what() << std::endl;
        return false;
    }
}

sf::Texture* AssetManager::getTexture(const std::string& name)
{
    auto it = textures.find(name);
    if (it != textures.end())
    {
        return it->second.get();
    }
    std::cerr << "Texture not found: " << name << std::endl;
    return nullptr;
}

bool AssetManager::loadFont(const std::string& name, const std::string& filepath)
{
    try
    {
        // SFML 3 Font also uses constructor
        auto font = std::make_unique<sf::Font>(filepath);
        std::cout << "Loaded font: " << name << " from " << filepath << std::endl;
        fonts[name] = std::move(font);
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Failed to load font: " << filepath << " - " << e.what() << std::endl;
        return false;
    }
}

sf::Font* AssetManager::getFont(const std::string& name)
{
    auto it = fonts.find(name);
    if (it != fonts.end())
    {
        return it->second.get();
    }
    std::cerr << "Font not found: " << name << std::endl;
    return nullptr;
}

bool AssetManager::loadSound(const std::string& name, const std::string& filepath)
{
    try
    {
        auto soundBuffer = std::make_unique<sf::SoundBuffer>(filepath);
        std::cout << "Loaded sound: " << name << " from " << filepath << std::endl;
        soundBuffers[name] = std::move(soundBuffer);
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Failed to load sound: " << filepath << " - " << e.what() << std::endl;
        return false;
    }
}

sf::SoundBuffer* AssetManager::getSoundBuffer(const std::string& name)
{
    auto it = soundBuffers.find(name);
    if (it != soundBuffers.end())
    {
        return it->second.get();
    }
    std::cerr << "Sound buffer not found: " << name << std::endl;
    return nullptr;
}

bool AssetManager::loadAllAssets()
{
    bool success = true;
    int loadedCount = 0;
    int failedCount = 0;
    
    std::cout << "\n=== LOADING BACKGROUND ASSETS ===" << std::endl;
    
    // Load nature1 background layers
    if (loadTexture("nature1_sky", "assets/backgrounds/nature1/sky.png")) loadedCount++; else { failedCount++; success = false; }
    if (loadTexture("nature1_clouds", "assets/backgrounds/nature1/clouds.png")) loadedCount++; else { failedCount++; success = false; }
    if (loadTexture("nature1_hills", "assets/backgrounds/nature1/hills.png")) loadedCount++; else { failedCount++; success = false; }
    if (loadTexture("nature1_grass", "assets/backgrounds/nature1/grass.png")) loadedCount++; else { failedCount++; success = false; }
    
    // Load nature2 background layers
    if (loadTexture("nature2_sky_stars", "assets/backgrounds/nature2/sky_stars.png")) loadedCount++; else { failedCount++; success = false; }
    if (loadTexture("nature2_aurora", "assets/backgrounds/nature2/aurora.png")) loadedCount++; else { failedCount++; success = false; }
    if (loadTexture("nature2_mountains", "assets/backgrounds/nature2/mountains.png")) loadedCount++; else { failedCount++; success = false; }
    
    // Load nature3 background layers
    if (loadTexture("nature3_sky_clouds", "assets/backgrounds/nature3/sky_clouds.png")) loadedCount++; else { failedCount++; success = false; }
    if (loadTexture("nature3_rocks", "assets/backgrounds/nature3/rocks.png")) loadedCount++; else { failedCount++; success = false; }
    
    std::cout << "\n=== LOADING CHARACTER ASSETS ===" << std::endl;
    
    // Load Fighter sprite sheets
    if (loadTexture("fighter_attack1", "assets/characters/Fighter/Attack_1.png")) loadedCount++; else { failedCount++; success = false; }
    if (loadTexture("fighter_attack2", "assets/characters/Fighter/Attack_2.png")) loadedCount++; else { failedCount++; success = false; }
    if (loadTexture("fighter_attack3", "assets/characters/Fighter/Attack_3.png")) loadedCount++; else { failedCount++; success = false; }
    if (loadTexture("fighter_dead", "assets/characters/Fighter/Dead.png")) loadedCount++; else { failedCount++; success = false; }
    if (loadTexture("fighter_hurt", "assets/characters/Fighter/Hurt.png")) loadedCount++; else { failedCount++; success = false; }
    if (loadTexture("fighter_idle", "assets/characters/Fighter/Idle.png")) loadedCount++; else { failedCount++; success = false; }
    if (loadTexture("fighter_jump", "assets/characters/Fighter/Jump.png")) loadedCount++; else { failedCount++; success = false; }
    if (loadTexture("fighter_run", "assets/characters/Fighter/Run.png")) loadedCount++; else { failedCount++; success = false; }
    if (loadTexture("fighter_shield", "assets/characters/Fighter/Shield.png")) loadedCount++; else { failedCount++; success = false; }
    if (loadTexture("fighter_walk", "assets/characters/Fighter/Walk.png")) loadedCount++; else { failedCount++; success = false; }
    
    // Load Samurai sprite sheets
    if (loadTexture("samurai_attack1", "assets/characters/Samurai/Attack_1.png")) loadedCount++; else { failedCount++; success = false; }
    if (loadTexture("samurai_attack2", "assets/characters/Samurai/Attack_2.png")) loadedCount++; else { failedCount++; success = false; }
    if (loadTexture("samurai_attack3", "assets/characters/Samurai/Attack_3.png")) loadedCount++; else { failedCount++; success = false; }
    if (loadTexture("samurai_dead", "assets/characters/Samurai/Dead.png")) loadedCount++; else { failedCount++; success = false; }
    if (loadTexture("samurai_hurt", "assets/characters/Samurai/Hurt.png")) loadedCount++; else { failedCount++; success = false; }
    if (loadTexture("samurai_idle", "assets/characters/Samurai/Idle.png")) loadedCount++; else { failedCount++; success = false; }
    if (loadTexture("samurai_jump", "assets/characters/Samurai/Jump.png")) loadedCount++; else { failedCount++; success = false; }
    if (loadTexture("samurai_run", "assets/characters/Samurai/Run.png")) loadedCount++; else { failedCount++; success = false; }
    if (loadTexture("samurai_shield", "assets/characters/Samurai/Shield.png")) loadedCount++; else { failedCount++; success = false; }
    if (loadTexture("samurai_walk", "assets/characters/Samurai/Walk.png")) loadedCount++; else { failedCount++; success = false; }
    
    // Load Shinobi sprite sheets
    if (loadTexture("shinobi_attack1", "assets/characters/Shinobi/Attack_1.png")) loadedCount++; else { failedCount++; success = false; }
    if (loadTexture("shinobi_attack2", "assets/characters/Shinobi/Attack_2.png")) loadedCount++; else { failedCount++; success = false; }
    if (loadTexture("shinobi_attack3", "assets/characters/Shinobi/Attack_3.png")) loadedCount++; else { failedCount++; success = false; }
    if (loadTexture("shinobi_dead", "assets/characters/Shinobi/Dead.png")) loadedCount++; else { failedCount++; success = false; }
    if (loadTexture("shinobi_hurt", "assets/characters/Shinobi/Hurt.png")) loadedCount++; else { failedCount++; success = false; }
    if (loadTexture("shinobi_idle", "assets/characters/Shinobi/Idle.png")) loadedCount++; else { failedCount++; success = false; }
    if (loadTexture("shinobi_jump", "assets/characters/Shinobi/Jump.png")) loadedCount++; else { failedCount++; success = false; }
    if (loadTexture("shinobi_run", "assets/characters/Shinobi/Run.png")) loadedCount++; else { failedCount++; success = false; }
    if (loadTexture("shinobi_shield", "assets/characters/Shinobi/Shield.png")) loadedCount++; else { failedCount++; success = false; }
    if (loadTexture("shinobi_walk", "assets/characters/Shinobi/Walk.png")) loadedCount++; else { failedCount++; success = false; }
    
    std::cout << "\n=== LOADING AUDIO ASSETS ===" << std::endl;
    
    // Load audio files
    if (loadSound("background_music", "assets/audio/background.mp3")) loadedCount++; else { failedCount++; success = false; }
    if (loadSound("success_sound", "assets/audio/success.mp3")) loadedCount++; else { failedCount++; success = false; }
    if (loadSound("jump_sound", "assets/audio/jump.mp3")) loadedCount++; else { failedCount++; success = false; }
    
    std::cout << "\n=== ASSET LOADING SUMMARY ===" << std::endl;
    std::cout << "Successfully loaded: " << loadedCount << " assets" << std::endl;
    if (failedCount > 0)
    {
        std::cout << "Failed to load: " << failedCount << " assets" << std::endl;
    }
    
    return success;
}
