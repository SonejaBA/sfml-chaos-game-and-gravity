#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <cmath>

using namespace sf;
using namespace std;


class Source {
public:
	Source(float pos_x, float pos_y, int radius);
	void render(RenderWindow& window);
	Vector2f getPos() const;
	float getStrength() const;
	int getRadius() const;

private:
	Vector2f pos;
	float strength;
	CircleShape body;
	int radius;
};