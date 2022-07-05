#pragma once
#include <iostream>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <string>
#include "Player.h"
#include "Block.h"
#include <vector>
#include <memory>
#include "Config.h"

class LevelManager;

class GameManager{
private:
    std::unordered_map<std::string, sf::Texture> texture_pool;
    std::vector<Player> players;
    std::vector<Block> blocks;
    std::vector<Block> decorationBlocks;
    std::vector<std::unique_ptr<Bullet>> bullets;

public:
    int play(sf::RenderWindow& window);

    friend LevelManager;
};
