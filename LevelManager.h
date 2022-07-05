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
#include "GameManager.h"

class LevelManager{
public:
    static bool loadLevel(GameManager& gm, std::string fileName);
};
