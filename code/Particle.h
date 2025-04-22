#pragma once
#include "Source.h"

class Particle {
public:
	Particle(float pos_x, float pos_y, float vel_x, float vel_y);
	void render(RenderWindow& window);
	Vector2f getPos() const;
	Vector2f getVel() const;
	void updatePhysics(const Source& s);

private:
	Vector2f pos;
	Vector2f vel;
	CircleShape body;
	Color col;

};