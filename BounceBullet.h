#pragma once
#include <SFML/Graphics.hpp>
#include "Updateable.h"
#include "Collider.h"
#include "Bullet.h"
#include <memory>

class BounceBullet : public BulletCRTP<BounceBullet> {

public:
    virtual void update(float deltaTime) override;
    virtual void onCollision(sf::Vector2f direction) override;

    BounceBullet() = default;

    BounceBullet(sf::Vector2f _position, sf::Vector2f _velocity, sf::Texture* _texture, short _damage = 1, int _bounces = 3);

protected:
    int bounces = 3;
};