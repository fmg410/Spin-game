#pragma once
#include <SFML/Graphics.hpp>
#include "Updateable.h"
#include "Collider.h"
#include <memory>

class Player;
class Bullet : public Updateable {

public:
    virtual void update(float deltaTime) override;
    virtual void onCollision(sf::Vector2f direction);
    void setPosition(sf::Vector2f pos) {body.setPosition(pos);}
    void setVelocity(sf::Vector2f vel) {velocity = vel;}
    void setDamage(short d) {damage = d;}
    void setOwnerId(char id) {ownerId = id;}
    void draw(sf::RenderWindow& window) {window.draw(body);}
    bool isDestroyed() {return toDelete;}
    bool hitPlayer(Player& player);
    void setTexture(sf::Texture* _bullet_texture) {bullet_texture = _bullet_texture; body.setTexture(bullet_texture);}
    Collider getCollider(){return Collider(body);}

    virtual std::unique_ptr<Bullet> clone() const { return std::make_unique<Bullet>(*this);}

    Bullet() {body.setFillColor(sf::Color::Magenta); body.setOrigin(body.getSize() / 2.f);}

    Bullet(sf::Vector2f _position, sf::Vector2f _velocity, sf::Texture* _texture, short _damage = 1);

    virtual ~Bullet() = default;

protected:
    sf::Vector2f velocity;
    short damage = 1;
    char ownerId = 0;
    bool toDelete = false;

private:
    sf::Texture* bullet_texture = nullptr;
    sf::RectangleShape body = sf::RectangleShape(sf::Vector2f(10.f, 10.f));
};

template <typename Derived>
class BulletCRTP : public Bullet {
public:
  virtual std::unique_ptr<Bullet> clone() const {
      return std::make_unique<Derived>((static_cast<Derived const&>(*this)));
  }

  BulletCRTP() = default;

  BulletCRTP(sf::Vector2f _position, sf::Vector2f _velocity, sf::Texture* texture, short _damage = 1)
    : Bullet(_position, _velocity, texture, _damage)
    {}
};