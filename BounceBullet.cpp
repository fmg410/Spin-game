#include "BounceBullet.h"
#include "Player.h"
#include <iostream>

void BounceBullet::update(float deltaTime) {
    Bullet::update(deltaTime);
}

void BounceBullet::onCollision(sf::Vector2f direction) {
    if(!bounces--) {
        toDelete = true;
    }
    else {

        if(direction.x) {
            velocity.x = -velocity.x;
        }
        else if(direction.y) {
            velocity.y = -velocity.y;
        }
    }
}

BounceBullet::BounceBullet(sf::Vector2f _position, sf::Vector2f _velocity, sf::Texture* _texture, short _damage, int _bounces)
    : BulletCRTP(_position, _velocity, _texture, _damage)
    , bounces(_bounces)
{}