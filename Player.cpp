#include "Player.h"
#include <math.h>
#include <cmath>

Player::Player(sf::Vector2f size, sf::Vector2f pos, sf::Texture *texture, sf::Texture *arrow_texture, sf::Texture *player_animation, char _id, sf::SoundBuffer& _gunShot, sf::SoundBuffer& _pickUp)
	: Player()
{
	body.setPosition(pos);
	body.setSize(size);
	body.setOrigin(body.getSize() / 2.0f);
	body.setTexture(texture);
	arrow.setSize(sf::Vector2f(20.f, 40.f));
	arrow.setOrigin(sf::Vector2f(10.0f, 0.f));
	arrow.setTexture(arrow_texture);
	playerId = _id;
	gunShot.setBuffer(_gunShot);
	gunShot.setVolume(20.0f);
	pickUp.setBuffer(_pickUp);
	pickUp.setVolume(100.0f);
}

void Player::update(float deltaTime){
	sf::Vector2f generalVelocity = {0.f, 0.f};

	switch(direction) {
		case Direction::DOWN:
		generalVelocity = velocity;
		break;
		case Direction::RIGHT:
		generalVelocity.y = velocity.x;
		generalVelocity.x = -velocity.y;
		break;
		case Direction::LEFT:
		generalVelocity.y = -velocity.x;
		generalVelocity.x = velocity.y;
		break;
		case Direction::UP:
		generalVelocity = -velocity;
		break;
	}

	generalVelocity.x = 0;

    if (left) {
		generalVelocity.x -= speed;
		faceRight = false;
	}
	if (right) {
		generalVelocity.x += speed;
		faceRight = true;
	}

	if (jump && canJump)
	{
		canJump = false;

		generalVelocity.y = -sqrtf(2.0f * 981.0f * jumpHeight);
	}

	generalVelocity.y += 981.0f * deltaTime;

	if (generalVelocity.x >= 0)
		faceRight = true;
	else
		faceRight = false;

	switch(direction) {
		case Direction::DOWN:
		velocity = generalVelocity;
		break;
		case Direction::RIGHT:
		velocity.x = generalVelocity.y;
		velocity.y = -generalVelocity.x;
		break;
		case Direction::LEFT:
		velocity.x = -generalVelocity.y;
		velocity.y = generalVelocity.x;
		break;
		case Direction::UP:
		velocity = -generalVelocity;
		break;
	}

	body.move(velocity * deltaTime);
	right = false;
	left = false;
	jump = false;

	weapon->update(deltaTime);

	if(immunityFrame > 0)
		immunityFrame -= deltaTime;

	rotation += Hz * 360.f * deltaTime * rotationDirection;

	while (rotation >= 360.f)
		rotation -= 360.f;
	while (rotation < 0.f)
		rotation += 360.f;

	arrow.setPosition(body.getPosition());
	arrow.setRotation(rotation - 90.f);

}

void Player::onCollision(sf::Vector2f direction)
{
	Direction collisionDirection = Direction::DOWN;
	sf::Vector2f generalVelocity = {0.f, 0.f};
	generalVelocity = translateToDown(velocity, Player::direction);

	if (direction.x < 0.0f)
	{
		// collision on the right
		collisionDirection = Direction::RIGHT;
	}
	else if (direction.x > 0.0f)
	{
		// collision of the left
		collisionDirection = Direction::LEFT;
	}
	if (direction.y < 0.0f)
	{
		// collision on the bottom
		collisionDirection = Direction::DOWN;
	}
	else if (direction.y > 0.0f)
	{
		// collision on the top
		collisionDirection = Direction::UP;
	}

	{
		short collisionShort = static_cast<short>(collisionDirection) - static_cast<short>(Player::direction) + 180;
		if(collisionShort == 360)
			collisionShort = 0;
		collisionDirection = static_cast<Direction>(collisionShort);
	}

	if (collisionDirection == Direction::RIGHT)
	{
		// collision on the right
		generalVelocity.x = 0.0f;
	}
	else if (collisionDirection == Direction::LEFT)
	{
		// collision of the left
		generalVelocity.x = 0.0f;
	}
	if (collisionDirection == Direction::DOWN)
	{
		// collision on the bottom
		generalVelocity.y = 0.0f;
		canJump = true;
		canSpin = true;
	}
	else if (collisionDirection == Direction::UP)
	{
		// collision on the top
		generalVelocity.y = 0.0f;
	}
	velocity = translateFromDown(generalVelocity, Player::direction);
}

void Player::draw(sf::RenderWindow& window) {
	if(!faceRight) {
		auto left = body;
		left.scale(sf::Vector2f(-1.f, 1.f));
		window.draw(left);
	}
	else {
		window.draw(body);
	}
	window.draw(arrow);
}

void Player::setAmmo(Ammunition _ammo, bool playSound) {
	if(playSound)
		pickUp.play();
	ammo = std::move(_ammo);
}

bool Player::shoot(std::vector<std::unique_ptr<Bullet>>& bullets) {
	bool t = weapon->shoot(body.getPosition(), rotation, ammo, bullets, playerId, body.getSize());
	if(t)
		gunShot.play();
	return t;
}

bool Player::rotateClockwise() {
	if(canSpin) {
		short dir = static_cast<short>(direction);
		dir += 90;
		if(dir > 270)
			dir = 0;
		direction = static_cast<Direction>(dir);
		canSpin = false;
		body.rotate(90.f);
		return true;
	}
	return false;
}

bool Player::rotateCounterClockwise() {
		if(canSpin) {
		short dir = static_cast<short>(direction);
		dir -= 90;
		if(dir < 0)
			dir = 270;
		direction = static_cast<Direction>(dir);
		canSpin = false;
		body.rotate(-90.f);
		return true;
	}
	return false;
}

sf::Vector2f translateToDown(sf::Vector2f velocity, Direction from) {
	sf::Vector2f generalVelocity = {0.f, 0.f};
	switch(from) {
		case Direction::DOWN:
		generalVelocity = velocity;
		break;
		case Direction::RIGHT:
		generalVelocity.y = velocity.x;
		generalVelocity.x = -velocity.y;
		break;
		case Direction::LEFT:
		generalVelocity.y = -velocity.x;
		generalVelocity.x = velocity.y;
		break;
		case Direction::UP:
		generalVelocity.x = -velocity.x;
		generalVelocity.y = -velocity.y;
		break;
	}
	return generalVelocity;
}

sf::Vector2f translateFromDown(sf::Vector2f generalVelocity, Direction to) {
	sf::Vector2f velocity = {0.f, 0.f};
	switch(to) {
		case Direction::DOWN:
		velocity = generalVelocity;
		break;
		case Direction::RIGHT:
		velocity.x = generalVelocity.y;
		velocity.y = -generalVelocity.x;
		break;
		case Direction::LEFT:
		velocity.x = -generalVelocity.y;
		velocity.y = generalVelocity.x;
		break;
		case Direction::UP:
		velocity = -generalVelocity;
		break;
	}
	return velocity;
}