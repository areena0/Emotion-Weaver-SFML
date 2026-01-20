#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <memory>
#include <iostream>

class AssetManager
{
public:
    AssetManager() = default;

    // Load a texture and store it with a key
    bool loadTexture(const std::string& name, const std::string& filepath);

    // Get a loaded texture
    sf::Texture* getTexture(const std::string& name);

    // Load a font
    bool loadFont(const std::string& name, const std::string& filepath);

    // Get a loaded font
    sf::Font* getFont(const std::string& name);

    // Load a sound buffer
    bool loadSound(const std::string& name, const std::string& filepath);

    // Get a loaded sound buffer
    sf::SoundBuffer* getSoundBuffer(const std::string& name);

    // Load all game assets
    bool loadAllAssets();

private:
    std::unordered_map<std::string, std::unique_ptr<sf::Texture>> textures;
    std::unordered_map<std::string, std::unique_ptr<sf::Font>> fonts;
    std::unordered_map<std::string, std::unique_ptr<sf::SoundBuffer>> soundBuffers;
};
