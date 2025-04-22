#include "Source.h"
#include "Particle.h"

Particle::Particle(float pos_x, float pos_y, float vel_x, float vel_y) {
	int firstRandColVal = rand() % 255 + 1;
	int secondRandColVal = rand() % 255 + 1;
	int thirdRandColVal = rand() % 255 + 1;

	pos.x = pos_x;
	pos.y = pos_y;
	
	vel.x = vel_x;
	vel.y = vel.y;

	body.setPosition(pos);
	body.setRadius(1);

	// particle could be some shade of blue or yellow
	body.setFillColor(Color(firstRandColVal, secondRandColVal, thirdRandColVal));

}

void Particle::render(RenderWindow& window) {
	body.setPosition(pos);
	window.draw(body);
}

Vector2f Particle::getPos() const
{
	return pos;
}

Vector2f Particle::getVel() const
{
	return vel;
}



void Particle::updatePhysics(const Source& s){
	// + radius to roughly center the pull
	float differenceX = s.getPos().x + s.getRadius() - pos.x;
	float differenceY = s.getPos().y + s.getRadius() - pos.y;

	float distance = sqrt(differenceX * differenceX + differenceY * differenceY);
	float inverseDistance = 1.0f / distance; 

	//vector normalization
	float normalizedX = inverseDistance * differenceX;
	float normalizedY = inverseDistance * differenceY;

	//inverse square law

	float inverseSquareDropOff = inverseDistance * inverseDistance;

	float accelerationX = normalizedX * s.getStrength() * inverseSquareDropOff;
	float accelerationY = normalizedY * s.getStrength() * inverseSquareDropOff;

	vel.x += accelerationX;
	vel.y += accelerationY;

	pos.x += vel.x;
	pos.y += vel.y;

}

