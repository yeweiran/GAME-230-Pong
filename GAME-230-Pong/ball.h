#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

using namespace sf;

class ball
{
public:
	ball(float radius, int WIDTH, int HEIGHT, int initVel);
	~ball();
	int SetVel(Vector2f newVel);
	int UpdatePosition(float dt);
	CircleShape getBall();
	Vector2f getVel();
	int reset(int turn);

private:
	CircleShape ballShape;
	Vector2f vel;
	int initVel;
	int WIDTH;
	int HEIGHT;
};

