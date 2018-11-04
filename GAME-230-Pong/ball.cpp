#include "ball.h"

ball::ball(float radius, int WIDTH, int HEIGHT,int initVel)
{
	ballShape.setRadius(radius);
	ballShape.setOrigin(radius, radius);
	ballShape.setFillColor(Color::Red);
	ballShape.setPosition(WIDTH / 2, HEIGHT / 2);
	this->initVel = initVel;
	vel = Vector2f(initVel,0);
	this->WIDTH = WIDTH;
	this->HEIGHT = HEIGHT;
}

ball::~ball()
{
}

int ball::SetVel(Vector2f newVel) {
	vel.x = newVel.x;
	vel.y = newVel.y;
	return 0;
}

int ball::UpdatePosition(float dt) {

	ballShape.setPosition(ballShape.getPosition() + vel * dt);
	return 0;
}

CircleShape ball::getBall() {
	return ballShape;
}

Vector2f ball::getVel() {
	return vel;
}

int ball::reset(int turn) {
	ballShape.setPosition(WIDTH / 2, HEIGHT / 2);
	if (turn % 2 == 0) {
		vel = Vector2f(initVel, 0);
	}
	else {
		vel = Vector2f(-initVel, 0);
	}
	return 0;
}
