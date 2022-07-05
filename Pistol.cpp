#include "Pistol.h"
#include <math.h>

#define PI 3.14159265

bool Pistol::shoot(sf::Vector2f pos, float rotation, Ammunition& ammo, std::vector<std::unique_ptr<Bullet>>& bullets, char ownerId, sf::Vector2f playerSize) {
    if(cooldown <= 0) {
        Bullet* bullet = bullets.emplace_back(ammo.getAmmo(1)).get();
        sf::Vector2f direction = {cos(rotation * PI / 180.0), sin(rotation * PI / 180.0)};
        bullet->setVelocity(direction * bulletSpeed);
        sf::Vector2f posNew = pos;
        while((posNew.x < (pos.x + playerSize.x / 2.f)) && (posNew.x > (pos.x - playerSize.x / 2.f)) && (posNew.y < (pos.y + playerSize.y / 2.f)) && (posNew.y > (pos.y - playerSize.y / 2.f))) {
            posNew += direction;
        }
        bullet->setPosition(posNew);
        bullet->setOwnerId(ownerId);
        cooldown = 1.f;
        return true;
    }
    return false;
}

void Pistol::update(float deltaTime) {
    if(cooldown > 0)
		cooldown -= deltaTime;
}