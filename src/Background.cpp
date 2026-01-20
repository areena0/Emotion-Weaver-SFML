#include "Background.h"
#include "AssetManager.h"
#include <cmath>

Background::Background(Type type, AssetManager* assetMgr, sf::Vector2u winSize)
    : backgroundType(type)
    , parallaxEnabled(true)
    , parallaxDir(1.0f, 0.0f)
    , emotionTint(sf::Color::White)
    , windowSize(winSize)
{
    switch (type)
    {
    case Type::Nature1:
        setupNature1(assetMgr, winSize);
        break;
    case Type::Nature2:
        setupNature2(assetMgr, winSize);
        break;
    case Type::Nature3:
        setupNature3(assetMgr, winSize);
        break;
    }
}

void Background::setupNature1(AssetManager* assetMgr, sf::Vector2u windowSize)
{
    // Nature1: sky -> clouds -> hills -> grass
    // Only sky elements drift horizontally; ground is static
    
    layers.clear();
    
    // Sky (slow drift)
    auto* skyTex = assetMgr->getTexture("nature1_sky");
    if (skyTex)
    {
        BackgroundLayer skyLayer(skyTex, 0.3f);
        float scaleX = static_cast<float>(windowSize.x) / skyTex->getSize().x;
        float scaleY = static_cast<float>(windowSize.y) / skyTex->getSize().y;
        skyLayer.sprite->setScale({scaleX, scaleY});
        if (skyLayer.spriteClone)
        {
            skyLayer.spriteClone->setScale({scaleX, scaleY});
        }
        skyLayer.wrapWidth = static_cast<float>(windowSize.x);
        layers.push_back(std::move(skyLayer));
    }
    
    // Clouds (moderate drift - sky element)
    auto* cloudsTex = assetMgr->getTexture("nature1_clouds");
    if (cloudsTex)
    {
        BackgroundLayer cloudsLayer(cloudsTex, 0.5f);
        float scaleX = static_cast<float>(windowSize.x) / cloudsTex->getSize().x;
        float scaleY = static_cast<float>(windowSize.y) / cloudsTex->getSize().y;
        cloudsLayer.sprite->setScale({scaleX, scaleY});
        if (cloudsLayer.spriteClone)
        {
            cloudsLayer.spriteClone->setScale({scaleX, scaleY});
        }
        cloudsLayer.wrapWidth = static_cast<float>(windowSize.x);
        layers.push_back(std::move(cloudsLayer));
    }
    
    // Hills (static - ground element)
    auto* hillsTex = assetMgr->getTexture("nature1_hills");
    if (hillsTex)
    {
        BackgroundLayer hillsLayer(hillsTex, 0.0f);
        float scaleX = static_cast<float>(windowSize.x) / hillsTex->getSize().x;
        float scaleY = static_cast<float>(windowSize.y) / hillsTex->getSize().y;
        hillsLayer.sprite->setScale({scaleX, scaleY});
        layers.push_back(std::move(hillsLayer));
    }
    
    // Grass (static - ground element)
    auto* grassTex = assetMgr->getTexture("nature1_grass");
    if (grassTex)
    {
        BackgroundLayer grassLayer(grassTex, 0.0f);
        float scaleX = static_cast<float>(windowSize.x) / grassTex->getSize().x;
        float scaleY = static_cast<float>(windowSize.y) / grassTex->getSize().y;
        grassLayer.sprite->setScale({scaleX, scaleY});
        layers.push_back(std::move(grassLayer));
    }
}

void Background::setupNature2(AssetManager* assetMgr, sf::Vector2u windowSize)
{
    // Nature2: sky_stars -> aurora -> mountains
    // Stars and aurora drift (sky); mountains are static (ground)
    
    layers.clear();
    
    // Starry sky (gentle drift)
    auto* skyTex = assetMgr->getTexture("nature2_sky_stars");
    if (skyTex)
    {
        BackgroundLayer skyLayer(skyTex, 0.2f);
        float scaleX = static_cast<float>(windowSize.x) / skyTex->getSize().x;
        float scaleY = static_cast<float>(windowSize.y) / skyTex->getSize().y;
        skyLayer.sprite->setScale({scaleX, scaleY});
        if (skyLayer.spriteClone)
        {
            skyLayer.spriteClone->setScale({scaleX, scaleY});
        }
        skyLayer.wrapWidth = static_cast<float>(windowSize.x);
        layers.push_back(std::move(skyLayer));
    }
    
    // Aurora (slow magical drift - sky phenomenon)
    auto* auroraTex = assetMgr->getTexture("nature2_aurora");
    if (auroraTex)
    {
        BackgroundLayer auroraLayer(auroraTex, 0.4f);
        float scaleX = static_cast<float>(windowSize.x) / auroraTex->getSize().x;
        float scaleY = static_cast<float>(windowSize.y) / auroraTex->getSize().y;
        auroraLayer.sprite->setScale({scaleX, scaleY});
        if (auroraLayer.spriteClone)
        {
            auroraLayer.spriteClone->setScale({scaleX, scaleY});
        }
        auroraLayer.wrapWidth = static_cast<float>(windowSize.x);
        layers.push_back(std::move(auroraLayer));
    }
    
    // Mountains (static - ground element)
    auto* mountainsTex = assetMgr->getTexture("nature2_mountains");
    if (mountainsTex)
    {
        BackgroundLayer mountainsLayer(mountainsTex, 0.0f);
        float scaleX = static_cast<float>(windowSize.x) / mountainsTex->getSize().x;
        float scaleY = static_cast<float>(windowSize.y) / mountainsTex->getSize().y;
        mountainsLayer.sprite->setScale({scaleX, scaleY});
        layers.push_back(std::move(mountainsLayer));
    }
}

void Background::setupNature3(AssetManager* assetMgr, sf::Vector2u windowSize)
{
    // Nature3: sky_clouds -> rocks
    // Clouds drift (sky); rocks are static (ground)
    
    layers.clear();
    
    // Sky with clouds (moderate drift)
    auto* skyTex = assetMgr->getTexture("nature3_sky_clouds");
    if (skyTex)
    {
        BackgroundLayer skyLayer(skyTex, 0.35f);
        float scaleX = static_cast<float>(windowSize.x) / skyTex->getSize().x;
        float scaleY = static_cast<float>(windowSize.y) / skyTex->getSize().y;
        skyLayer.sprite->setScale({scaleX, scaleY});
        if (skyLayer.spriteClone)
        {
            skyLayer.spriteClone->setScale({scaleX, scaleY});
        }
        skyLayer.wrapWidth = static_cast<float>(windowSize.x);
        layers.push_back(std::move(skyLayer));
    }
    
    // Rocky hills (static - ground element)
    auto* rocksTex = assetMgr->getTexture("nature3_rocks");
    if (rocksTex)
    {
        BackgroundLayer rocksLayer(rocksTex, 0.0f);
        float scaleX = static_cast<float>(windowSize.x) / rocksTex->getSize().x;
        float scaleY = static_cast<float>(windowSize.y) / rocksTex->getSize().y;
        rocksLayer.sprite->setScale({scaleX, scaleY});
        layers.push_back(std::move(rocksLayer));
    }
}

void Background::update(float deltaTime)
{
    if (!parallaxEnabled)
        return;
    
    // Update parallax offset for each layer
    for (auto& layer : layers)
    {
        if (layer.parallaxSpeed > 0.0f)
        {
            // Slow, subtle drift
            layer.offset.x += parallaxDir.x * layer.parallaxSpeed * deltaTime * 10.0f;
            layer.offset.y += parallaxDir.y * layer.parallaxSpeed * deltaTime * 5.0f;
            
            // Wrap horizontally for seamless looping
            if (layer.offset.x > layer.wrapWidth)
            {
                layer.offset.x -= layer.wrapWidth;
            }
            else if (layer.offset.x < -layer.wrapWidth)
            {
                layer.offset.x += layer.wrapWidth;
            }
            
            // Apply offset to sprite position
            layer.sprite->setPosition(layer.offset);
            
            // Position the clone sprite to create seamless wrapping
            if (layer.spriteClone)
            {
                sf::Vector2f cloneOffset = layer.offset;
                if (layer.offset.x >= 0)
                {
                    // Main sprite moving right, clone on the left
                    cloneOffset.x = layer.offset.x - layer.wrapWidth;
                }
                else
                {
                    // Main sprite moving left, clone on the right
                    cloneOffset.x = layer.offset.x + layer.wrapWidth;
                }
                layer.spriteClone->setPosition(cloneOffset);
            }
        }
    }
}

void Background::draw(sf::RenderWindow& window)
{
    // Draw all layers back to front
    for (auto& layer : layers)
    {
        if (layer.sprite)
        {
            window.draw(*layer.sprite);
            
            // Draw clone for seamless wrapping if this layer moves
            if (layer.spriteClone && layer.parallaxSpeed > 0.0f)
            {
                window.draw(*layer.spriteClone);
            }
        }
    }
}

void Background::setEmotionTint(const sf::Color& tint)
{
    emotionTint = tint;
    
    // Apply tint to all layers
    for (auto& layer : layers)
    {
        if (layer.sprite)
        {
            layer.sprite->setColor(tint);
        }
        if (layer.spriteClone)
        {
            layer.spriteClone->setColor(tint);
        }
    }
}

void Background::resetTint()
{
    setEmotionTint(sf::Color::White);
}
