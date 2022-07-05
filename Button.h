#pragma once
#include <iostream>
#include <string.h>
#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>


class Button{
    private:
    sf::RectangleShape button;
    sf::Text button_text;
    sf::Vector2f button_size;
    std::function<void()> callback = [](){};
    std::unique_ptr<sf::Texture> button_txt = std::make_unique<sf::Texture>();
    std::string textureName = "";

    public:

    Button();
    Button(std::string n_text,sf::Vector2f size, sf::Color bgColor, sf::Color textColor, int _textSize, sf::Vector2f bPosition, sf::Font& font, std::function<void()> _callback);
    Button(sf::Vector2f size, std::string txt_name, sf::Vector2f bPosition, std::function<void()> _callback);
    Button(const Button& b);
    Button(const Button&& b);
    Button& operator=(Button b);
    ~Button();

    void setFont(sf::Font &font);
    void setButtonColor(sf::Color bgColor);
    void setTextColor(sf::Color textColor);
    void setFontSize(int fontSize);
    void changeTexture(std::string newTxt);
    void setButtonPosition(sf::Vector2f position);
    void drawButton(sf::RenderWindow &window);
    bool isMouseOver(sf::RenderWindow &window);
    bool doIfPressed(sf::RenderWindow &window);
    void rotateButton(float angle);
    void changeString(std::string newString);
    std::string getTextureName();
};