#pragma once
#include "Bullet.h"
#include <memory>
#include "BounceBullet.h"

class Ammunition{
public:
    std::unique_ptr<Bullet> getAmmo(int needed);

    void setCount(int _count) {count = _count;}
    void setBulletType(std::unique_ptr<Bullet> _bulletType) {}
    int getCount() {return count;}

    Ammunition(std::unique_ptr<Bullet> _bulletType, sf::Texture* _bullet_texture, int _count);
    Ammunition() = default;
private:
    int count = 0;
    sf::Texture* bullet_texture = nullptr;
    std::unique_ptr<Bullet> bulletType = std::make_unique<Bullet>();
};