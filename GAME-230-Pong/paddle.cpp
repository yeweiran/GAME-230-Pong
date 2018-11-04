#include "paddle.h"

paddle::paddle(Vector2f size, int WIDTH, int HEIGHT, int side, Vector2f vel)
{
	rect.setSize(size);
	if (side == -1) {
		rect.setPosition(100, HEIGHT/2 - size.y/2);
	}
	else {
		rect.setPosition(WIDTH - 100, HEIGHT/2 - size.y / 2);
	}
	rect.setFillColor(Color::White);
	this->side = side;
	this->vel = vel;
	this->HEIGHT = HEIGHT;
	this->WIDTH = WIDTH;
}

paddle::~paddle()
{
}

RectangleShape paddle::getPaddle() {
	return rect;
}

int paddle::SetVel(Vector2f newVel) {
	//vel.x = newVel.x;
	vel.y = newVel.y;
	return 0;
}

int paddle::UpdatePosition(float dt, int dir) {
	if (dir == 0 && rect.getPosition().y >= 0) {
		rect.setPosition(rect.getPosition() + vel * dt);
	}
	else if(dir == 1 && rect.getPosition().y + rect.getSize().y <= HEIGHT){
		rect.setPosition(rect.getPosition() - vel * dt);
	}
	return 0;
}

int paddle::reset() {
	if (side == -1) {
		rect.setPosition(100, HEIGHT / 2 - rect.getSize().y / 2);
	}
	else {
		rect.setPosition(WIDTH - 100, HEIGHT / 2 - rect.getSize().y / 2);
	}
	return 0;
}