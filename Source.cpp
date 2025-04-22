#include "Source.h"

Source::Source(float pos_x, float pos_y, int radius) {
	const float STRENGTH = 5000;
	float sourceStrength = radius * STRENGTH * .2;

	pos.x = pos_x;
	pos.y = pos_y;
	strength = sourceStrength;
	this->radius = radius;

	body.setPosition(pos);
	body.setRadius(radius);

}

int Source::getRadius() const {
	return radius;
}

void Source::render(RenderWindow& window){
	body.setPosition(pos);
	window.draw(body);
}

Vector2f Source::getPos() const
{
	return pos;
}

float Source::getStrength() const {
	return strength;
}