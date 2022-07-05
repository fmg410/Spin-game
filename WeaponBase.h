#pragma once
#include "Bullet.h"
#include <SFML/Graphics.hpp>
#include "Ammunition.h"
#include <vector>

class WeaponBase{
    public:
    virtual bool shoot(sf::Vector2f pos, float rotation, Ammunition& ammo, std::vector<std::unique_ptr<Bullet>>& bullets, char ownerId, sf::Vector2f playerSize) = 0;
    virtual void update(float deltaTime) = 0;

    virtual ~WeaponBase() = default;
    private:
};