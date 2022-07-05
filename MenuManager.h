#pragma once
#include "Button.h"
#include <vector>
#include <string>
#include <functional>
#include <memory>
#include "MusicManager.h"

#define standardHeight 500
#define standardWidth 500

class MenuManager{
    public:
    std::vector<Button> buttons;
    sf::Vector2f menu_size;
    std::vector<std::function<void()>> panels;
    sf::RenderWindow& window;
    std::function<void()> additionalDraw = [](){};
    std::unique_ptr<sf::Texture> logo = std::make_unique<sf::Texture>();
    int won = 0;

    void initializePanels(sf::Vector2f menuSize, sf::Font& font);

    public:
    MenuManager(sf::Font& font, sf::RenderWindow& window);
    MenuManager(sf::Vector2f menuSize, sf::Font& font, sf::RenderWindow& window);
    ~MenuManager() = default;

    void drawMenu(sf::RenderWindow& window);
    void changeWindow(sf::RenderWindow& window);
    void checkButtons(sf::RenderWindow& window) {for(auto& b : buttons) {b.doIfPressed(window);}}
    void changePanel(int id) {panels.at(id)();}
};
