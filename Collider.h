#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

class Collider
{
public:
	Collider(sf::RectangleShape& body);

	void move(float dx, float dy) const { body.move(dx, dy); }

	bool checkCollision(const Collider& other, sf::Vector2f& direction, float push, bool moveBodies); // push : 0 - movable ; 1 - immovable
	sf::Vector2f getPosition() const { return body.getPosition(); }
	sf::Vector2f getHalfSize() const { return body.getSize() / 2.0f; }

private:
	sf::RectangleShape& body;
};

template<typename T, typename A>
void collide(T& body1, A& body2, float push, bool moveBodies, std::function<void()> func){
	sf::Vector2f direction;
	if(body1.getCollider().checkCollision(body2.getCollider(), direction, push, moveBodies)){
		body1.onCollision(direction);
		body2.onCollision(direction);
		func();
	}
}