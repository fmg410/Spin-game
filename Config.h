#pragma once
#include <SFML/Graphics.hpp>

class Config{
    public:
    static Config& getInstance();

    float getScreenWidth() { return screenWidth; }
    float getScreenHeight() { return screenHeight; }
    void setScreenWidth(float w) { screenWidth = w; }
    void setScreenHeight(float h) { screenHeight = h; }
    sf::Vector2f getBlockSize() {return blockSize; }

    sf::Font c_font{};

    private:
    float screenWidth = 2048.f;
    float screenHeight = 1024.f;
    sf::Vector2f blockSize {32.0f,32.0f};





    Config();
    Config(const Config& c) = delete;
    Config(const Config&& c) = delete;
};