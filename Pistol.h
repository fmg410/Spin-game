#pragma once
#include "WeaponBase.h"
#include <memory>

class Pistol : public WeaponBase {

public:
    virtual bool shoot(sf::Vector2f pos, float rotation, Ammunition& ammo, std::vector<std::unique_ptr<Bullet>>& bullets, char ownerId, sf::Vector2f playerSize) override;
    virtual void update(float deltaTime) override;

private:
    const float bulletSpeed = 600.f;
    float cooldown = 0.f;
};