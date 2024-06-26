#include "Collider.h"
#include <iostream>
#include <math.h>

Collider::Collider(sf::RectangleShape& body)
	: body(body)
{}

bool Collider::checkCollision(const Collider& other, sf::Vector2f& direction, float push, bool moveBodies) // possible create another method to handle collision to then inherit after this class to collide with bullet and desintegrate it or with wall and stop
{
	sf::Vector2f otherPosition = other.getPosition();
	sf::Vector2f otherHalfSize = other.getHalfSize();
	sf::Vector2f thisPosition = getPosition();
	sf::Vector2f thisHalfSize = getHalfSize();

	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;
	float intersectX = fabs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = fabs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		push = std::min(std::max(push, 0.0f), 1.0f);

		if (intersectX > intersectY)
		{
			if (deltaX > 0.0f)
			{
				if(moveBodies) {
					move(intersectX * (1.0f - push), 0.0f);
					other.move(-intersectX * push, 0.0f);
				}
				direction.x = 1.0f;
				direction.y = 0.0f;
			}
			else
			{
				if(moveBodies) {
					move(-intersectX * (1.0f - push), 0.0f);
					other.move(intersectX * push, 0.0f);
				}
				direction.x = -1.0f;
				direction.y = 0.0f;
			}
		}
		else
		{
			if (deltaY > 0.0f)
			{
				if(moveBodies) {
					move(0.0f, intersectY * (1.0f - push));
					other.move(0.0f, -intersectY * push);
				}
				direction.x = 0.0f;
				direction.y = 1.0f;
			}
			else
			{
				if(moveBodies) {
					move(0.0f, -intersectY * (1.0f - push));
					other.move(0.0f, intersectY * push);
				}
				direction.x = 0.0f;
				direction.y = -1.0f;
			}
		}

		return true;
	}

	return false;
}
