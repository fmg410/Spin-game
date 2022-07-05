#include "Block.h"

Block::Block(){
   block_size = sf::Vector2f(50.0f,50.0f);
   block.setFillColor(sf::Color::Red);
   block.setPosition(100.0f,100.0f);
   block.setSize(block_size);
   block.setOrigin(block.getSize() / 2.0f);
}

Block::Block(sf::Color b_color, sf::Vector2f b_size, sf::Vector2f b_position){
    block_size=b_size;
    block.setFillColor(b_color);
    block.setPosition(b_position);
    block.setSize(block_size);
    block.setOrigin(block.getSize()/2.0f);
}

Block::Block(sf::Texture *txt, sf::Vector2f b_size, sf::Vector2f b_position){
    block_size = b_size;
    block.setTexture(txt);
    block.setSize(block_size);
    block.setOrigin(block.getSize()/2.0f);
    block.setPosition(b_position);
}
