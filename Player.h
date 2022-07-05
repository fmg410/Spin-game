#pragma once
#include <memory>
#include "Ammunition.h"
#include "WeaponBase.h"
#include "Updateable.h"
#include "Direction.h"
#include "Collider.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Player : public Updateable {

public:
    Player() = default;
    Player(sf::Vector2f size, sf::Vector2f pos, sf::Texture *texture,sf::Texture *arrow_texture,sf::Texture *player_animation, char _id, sf::SoundBuffer& _gunShot, sf::SoundBuffer& _pickUp);
    void update(float deltaTime) override;
    void onCollision(sf::Vector2f direction);

    void draw(sf::RenderWindow& window);
    sf::Vector2f getPosition() const { return body.getPosition(); }
    void setPosition(sf::Vector2f pos) { body.setPosition(pos); }
    Collider getCollider() { return Collider(body); }
    sf::RectangleShape getBody() {return body;}

    void goRight() {right = true;}
    void goLeft() {left = true;}
    void doJump() {jump = true;}
    void doDamage(int damageAmount = 1) { if(immunityFrame <= 0){ health -= damageAmount; immunityFrame = 3.f;}}
    int getHealth() { return health; }
    bool isAlive() { return health > 0; }
    void setId(char id) {playerId = id;}
    char getId() {return playerId;}
    void setWeapon(std::unique_ptr<WeaponBase> _weapon) {weapon = std::move(_weapon);}
    void setAmmo(Ammunition _ammo, bool playSound = true);
    void setAmmoCount(int count) {ammo.setCount(count);}
    void changeRotationDirection() {rotationDirection = -rotationDirection;}
    void setRotation(float r) {rotation = r;}
    int getAmmoCount() {return ammo.getCount();}
    void setHealth(int h) {health = h;}

    bool shoot(std::vector<std::unique_ptr<Bullet>>& bullets);

    bool rotateClockwise();
    bool rotateCounterClockwise();

private:
    sf::RectangleShape arrow;
    sf::RectangleShape body;
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Sound gunShot;
    sf::Sound pickUp;


    Ammunition ammo;
    std::unique_ptr<WeaponBase> weapon;

    Direction direction = Direction::DOWN;

    float speed = 200.f;
    float jumpHeight = 200.f;
    float shotDirection = 0.f;
    float immunityFrame = 0.f;

    float rotation = 0.f;
    float rotationDirection = 1.f;
    float Hz = 0.7f;

    int row = 0;
    int health = 1;
    char playerId = 0;

    bool canJump = true;
    bool canSpin = true;
    bool faceRight = true;

    bool right = false;
    bool left = false;
    bool jump = false;
};

sf::Vector2f translateToDown(sf::Vector2f velocity, Direction from);

sf::Vector2f translateFromDown(sf::Vector2f velocity, Direction to);