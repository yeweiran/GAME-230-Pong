#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

using namespace sf;

class paddle
{
public:
	paddle(Vector2f size, int WIDTH, int HEIGHT, int side, Vector2f vel);
	~paddle();
	RectangleShape getPaddle();
	int SetVel(Vector2f newVel);
	int UpdatePosition(float dt, int dir);
	int reset();

private:
	RectangleShape rect;
	Vector2f vel;
	int side;
	int WIDTH;
	int HEIGHT;
};

