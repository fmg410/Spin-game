#include "Button.h"
#include <iostream>

Button::Button()
{
    button_text.setString("empty button");
    button_text.setColor(sf::Color::Black);
    button.setSize(sf::Vector2f(100.0f, 100.0f));
    button.setFillColor(sf::Color::White);
    button.setPosition(sf::Vector2f(250, 250));
}

Button::Button(std::string n_text, sf::Vector2f size, sf::Color bgColor, sf::Color textColor, int _textSize, sf::Vector2f bPosition, sf::Font &_font, std::function<void()> _callback)
    : button_text(n_text, _font, _textSize), button(size), callback(_callback)
{
    button_text.setColor(textColor);
    button.setFillColor(bgColor);
    button.setPosition(bPosition);
    button.setOrigin(button.getSize() / 2.0f);

    sf::FloatRect textRect = button_text.getLocalBounds();

    int maxHeight = 0;

    for (size_t characterIndex = 0; characterIndex < n_text.size(); ++characterIndex)
    {
        int currentHeight = _font.getGlyph(n_text[characterIndex], button_text.getCharacterSize(), false).bounds.height;
        if (currentHeight > maxHeight)
        {
            maxHeight = currentHeight;
        }
    }

    button_text.setOrigin(textRect.left + textRect.width / 2.0f,
                          textRect.top + maxHeight / 2.0f);
    button_text.setPosition(button.getPosition());
}

Button::Button(sf::Vector2f size, std::string txt_name, sf::Vector2f bPosition, std::function<void()> _callback)
    : textureName(txt_name)
    , callback(_callback)
{
    button.setSize(size);
    button.setPosition(bPosition);
    button.setOrigin(button.getSize()/2.0f);
    button_txt->loadFromFile(textureName);
    button.setTexture(button_txt.get());
}

Button::~Button()
{
}

Button::Button(const Button &b)
{
    button = b.button;
    button_text = b.button_text;
    callback = b.callback;
    button_txt = std::make_unique<sf::Texture>(*b.button_txt.get());
    button.setTexture(button_txt.get());
}

Button::Button(const Button &&b)
{
    button = std::move(b.button);
    button_text = std::move(b.button_text);
    callback = std::move(b.callback);
    button_txt = std::make_unique<sf::Texture>(*b.button_txt.get());
    button.setTexture(button_txt.get());
}

Button& Button::operator=(Button b)
{
    button = std::move(b.button);
    button_text = std::move(b.button_text);
    callback = std::move(b.callback);
    button_txt = std::make_unique<sf::Texture>(*b.button_txt.get());
    button.setTexture(button_txt.get());
    return *this;
}

void Button::setFont(sf::Font &font)
{
    button_text.setFont(font);
}

void Button::setButtonColor(sf::Color bgColor)
{
    button.setFillColor(bgColor);
}

void Button::setTextColor(sf::Color textColor)
{
    button_text.setColor(textColor);
}

void Button::setFontSize(int fontSize)
{
    button_text.setCharacterSize(fontSize);
}

void Button::changeTexture(std::string newTxt){
    textureName = newTxt;
    button_txt->loadFromFile(newTxt);
}

void Button::setButtonPosition(sf::Vector2f position)
{
    button.setPosition(position);

    float xPos = (position.x + button.getLocalBounds().width / 2) - (button_text.getLocalBounds().width / 2);

    float yPos = (position.y + button.getLocalBounds().height / 2) - (button_text.getLocalBounds().height / 2);

    button_text.setPosition(xPos, yPos);
}

void Button::drawButton(sf::RenderWindow &window)
{
    window.draw(button);
    window.draw(button_text);
}

bool Button::isMouseOver(sf::RenderWindow &window)
{
    float mousePosX = sf::Mouse::getPosition(window).x;
    float mousePosY = sf::Mouse::getPosition(window).y;

    float buttonPosX = button.getPosition().x - button.getLocalBounds().width / 2.0f;
    float buttonPosY = button.getPosition().y - button.getLocalBounds().height / 2.0f;

    float buttonWidth = button.getPosition().x + button.getLocalBounds().width / 2.0f;
    float buttonHeight = button.getPosition().y + button.getLocalBounds().height / 2.0f;

    if (mousePosX < buttonWidth && mousePosX > buttonPosX && mousePosY < buttonHeight && mousePosY > buttonPosY)
    {
        return true;
    }
    return false;
}

bool Button::doIfPressed(sf::RenderWindow &window)
{
    if (isMouseOver(window))
    {
        callback();
        return true;
    }
    return false;
}

std::string Button::getTextureName() {
    return textureName;
}

void Button::rotateButton(float angle){
    button.rotate(angle);
}

void Button::changeString(std::string newString){
    button_text.setString(newString);
}