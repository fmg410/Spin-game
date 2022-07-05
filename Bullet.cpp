#include "Bullet.h"
#include "Player.h"
#include <iostream>

void Bullet::update(float deltaTime) {
    body.setPosition(body.getPosition() + velocity * deltaTime);
}

void Bullet::onCollision(sf::Vector2f direction) {
    toDelete = true;
}

bool Bullet::hitPlayer(Player& player) {
    if(player.getId() != ownerId && !toDelete) {
        toDelete = true;
        player.doDamage(damage);
        return true;
    }
    return false;
}

Bullet::Bullet(sf::Vector2f _position, sf::Vector2f _velocity, sf::Texture* _texture, short _damage)
    : velocity(_velocity)
    , damage(_damage)
{
    body.setPosition(_position);
    body.setFillColor(sf::Color::Magenta);
    body.setOrigin(body.getSize() / 2.f);
    body.setTexture(bullet_texture);
}