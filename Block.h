#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"

class Block{
    private:
    sf::RectangleShape block;
    sf::Vector2f block_size;
    std::string txt_name;

    public:
    Block();
    Block(sf::Color b_color, sf::Vector2f b_size,sf::Vector2f b_position);
    Block(sf::Texture *txt,sf::Vector2f b_size, sf::Vector2f b_position);
    Collider getCollider() { return Collider(block); }
    void draw(sf::RenderWindow& window) { window.draw(block); }
    void setPosition(sf::Vector2f pos) { block.setPosition(pos); }
    Block(sf::Vector2f pos) : Block() { setPosition(pos); }
    void onCollision(sf::Vector2f d) {}
};