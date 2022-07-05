#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameManager.h"
#include "MenuManager.h"
#include "MusicManager.h"
#include <vector>
#include "Config.h"

static const float VIEW_HEIGHT = 1024.0f;
static const float VIEW_WIDTH = 2048.0f;

int main()
{
    sf::RenderWindow window(sf::VideoMode(Config::getInstance().getScreenWidth(), Config::getInstance().getScreenHeight()), "Spin", sf::Style::Close | sf::Style::Resize);

    sf::Image icon;
    icon.loadFromFile(".\\Textures\\logo.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    GameManager game;
    //game.play(window);
    sf::Font font;
    //font.loadFromFile("Arialn.ttf");
    font.loadFromFile(".\\Fonts\\Future_Italic.ttf");
    Config::getInstance().c_font = font;
    MenuManager menu(sf::Vector2f(Config::getInstance().getScreenWidth(), Config::getInstance().getScreenHeight()), font, window);
    menu.changePanel(0);

    sf::RectangleShape background(sf::Vector2f(Config::getInstance().getScreenWidth(), Config::getInstance().getScreenHeight()));
    background.setPosition(0, 0);
    //background.setFillColor(sf::Color::Cyan);
    std::unique_ptr<sf::Texture> background_texture = std::make_unique<sf::Texture>();
    background_texture->loadFromFile(".\\Textures\\BackgroundCzysty.png");
    background.setTexture(background_texture.get());



    sf::Event evnt;
    sf::Music music;
    sf::SoundBuffer buffer;
    sf::SoundBuffer buffer2;
    sf::Sound sound;
    sound.setVolume(MusicManager::getInstance().getVolume());

    buffer2.loadFromFile(".\\Music\\item-equip-6904.wav");
    buffer.loadFromFile(".\\Music\\pistol-shot-14649.wav");

    sound.setBuffer(buffer);
    //sound.play();

    if(!music.openFromFile(".\\Music\\bground_music.wav")){
        std::cout<<"Failed to load background music file"<<std::endl;
    }

    music.setVolume(MusicManager::getInstance().getVolume());
    music.setLoop(true);
    music.play();

    sf::Sound s;

    while (window.isOpen())
    {
        while (window.pollEvent(evnt))
        {
            switch (evnt.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
                case sf::Event::KeyPressed:
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::H))
                {
                    s.setBuffer(buffer);
                s.play();
                std::cout << "H\n";
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::G))
                {
                sound.play();
                std::cout << "G\n";
                }
                break;
                case sf::Event::MouseButtonPressed:
                    if(evnt.mouseButton.button == sf::Mouse::Left)
                        menu.checkButtons(window);
                break;
            }
            window.clear();
            window.draw(background);
            menu.drawMenu(window);
            music.setVolume(MusicManager::getInstance().getVolume());
            /* sf::Text t("DZIALAM", font);
            t.setPosition(100.f, 200.f);
            t.setFillColor(sf::Color::Blue);
            window.draw(t); */
            window.display();
        }

        // game.play(window);
    }
    return 0;
}