#include"Ammunition.h"

std::unique_ptr<Bullet> Ammunition::getAmmo(int needed) {
    std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f), bullet_texture);
    bullet->setTexture(bullet_texture);
    if(needed <= count) {
        count -= needed;
        bullet = bulletType->clone();
    }
    return bullet;
}

Ammunition::Ammunition(std::unique_ptr<Bullet> _bulletType, sf::Texture* _bullet_texture, int _count)
    : bulletType(std::move(_bulletType))
    , count(_count)
    , bullet_texture(_bullet_texture)
{
    bulletType->setTexture(bullet_texture);
}
