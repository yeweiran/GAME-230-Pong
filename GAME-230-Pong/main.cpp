#include "ball.h"
#include "paddle.h"

using namespace sf;

int WIDTH = 1200;
int HEIGHT = 800;
int initVel = 500;
int tempVel;
int augPerHit = 25;
float radius = 16;
Vector2f paddleSize = Vector2f(20, 120);
Vector2f paddleVel = Vector2f(0, -100);
Font font;
int lScore;
int rScore;
Text lScoreText;
Text rScoreText;

enum mode {
	AI,
	PvP,
	Special
};
mode gameMode;

void update_state(float dt, ball &newBall, paddle &lPaddle, paddle &rPaddle);
void render_frame(ball &newBall, paddle &lPaddle, paddle &rPaddle);
int reset(ball &newBall, paddle &lPaddle, paddle &rPaddle);
float length(Vector2f v)
{
	return sqrtf(v.x*v.x + v.y*v.y);
}

RenderWindow window;

int main()
{
	window.create(VideoMode(WIDTH, HEIGHT), "Just Another Pong Game");
	gameMode = AI;
	Clock clock;

	ball newBall = ball(radius, WIDTH, HEIGHT, initVel);
	paddle lPaddle = paddle(paddleSize, WIDTH, HEIGHT, -1,paddleVel);
	paddle rPaddle = paddle(paddleSize, WIDTH, HEIGHT, 1,paddleVel);
	tempVel = initVel;
	font.loadFromFile("font.ttf");
	
	lScore = 0;
	rScore = 0;
	lScoreText.setFont(font);
	lScoreText.setCharacterSize(100);
	lScoreText.setString(std::to_string(lScore));
	lScoreText.setFillColor(Color::White);
	lScoreText.setPosition(50, 50);
	rScoreText.setFont(font);
	rScoreText.setCharacterSize(100);
	rScoreText.setString(std::to_string(rScore));
	rScoreText.setFillColor(Color::White);
	rScoreText.setPosition(WIDTH - 100, 50);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		float dt = clock.restart().asSeconds();

		update_state(dt,newBall,lPaddle,rPaddle);
		render_frame(newBall, lPaddle, rPaddle);
		window.display();
	}

	return 0;
}

void update_state(float dt, ball &newBall, paddle &lPaddle, paddle &rPaddle)
{
	Vector2f bp = newBall.getBall().getPosition();
	Vector2f lpp = lPaddle.getPaddle().getPosition();
	Vector2f rpp = rPaddle.getPaddle().getPosition();
	Vector2f temp;
	float len;
	//collision
	//lp
	if ((bp.x >= lpp.x && bp.x < lpp.x + paddleSize.x && (abs(lpp.y - bp.y) < radius || abs(bp.y - lpp.y - paddleSize.y) < radius))
		|| (bp.y > lpp.y && bp.y < lpp.y + paddleSize.y && bp.x - lpp.x - paddleSize.x < radius)
		|| length(Vector2f(bp.x - lpp.x - paddleSize.x,bp.y - lpp.y)) < radius
		|| length(Vector2f(bp.x - lpp.x - paddleSize.x, bp.y - lpp.y - paddleSize.y)) < radius) {
		temp = bp - Vector2f(lpp.x - paddleSize.y / 2, lpp.y + paddleSize.y / 2);
		len = length(temp);
		newBall.SetVel(Vector2f(temp.x*tempVel / len, temp.y*tempVel / len));
		tempVel += augPerHit;
	}
	//rp
	if ((bp.x > rpp.x && bp.x <= rpp.x + paddleSize.x && (abs(rpp.y - bp.y) < radius || abs(bp.y - rpp.y - paddleSize.y) < radius))
		|| (bp.y > rpp.y && bp.y < rpp.y + paddleSize.y && rpp.x - bp.x < radius)
		|| length(Vector2f(bp.x - rpp.x, bp.y - rpp.y)) < radius
		|| length(Vector2f(bp.x - rpp.x, bp.y - rpp.y - paddleSize.y)) < radius) {
		temp = bp - Vector2f(rpp.x + paddleSize.x + paddleSize.y / 2, rpp.y + paddleSize.y / 2);
		len = length(temp);
		newBall.SetVel(Vector2f(temp.x*tempVel / len, temp.y*tempVel / len));
		tempVel += augPerHit;
	}
	//board
	if (bp.y <= 0 || bp.y >= HEIGHT) {
		newBall.SetVel(Vector2f(newBall.getVel().x, -newBall.getVel().y));
	}
	
	//press up
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		rPaddle.UpdatePosition(dt, 0);
	}
	//press down
	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		rPaddle.UpdatePosition(dt, 1);
	}
	//AI
	if (gameMode == AI) {
		if (bp.y < lpp.y + paddleSize.y / 2) {
			lPaddle.UpdatePosition(dt, 0);
		}
		if (bp.y > lpp.y + paddleSize.y / 2) {
			lPaddle.UpdatePosition(dt, 1);
		}
	}
	newBall.UpdatePosition(dt);
	//score
	if (bp.x <= 0) {
		rScore++;
		rScoreText.setString(std::to_string(rScore));
		reset(newBall, lPaddle, rPaddle);
	}
	if (bp.x >= WIDTH) {
		lScore++;
		lScoreText.setString(std::to_string(lScore));
		reset(newBall, lPaddle, rPaddle);
	}
}

void render_frame(ball &newBall, paddle &lPaddle, paddle &rPaddle)
{
	window.clear();
	window.draw(lScoreText);
	window.draw(rScoreText);
	window.draw(newBall.getBall());
	window.draw(lPaddle.getPaddle());
	window.draw(rPaddle.getPaddle());
}

int reset(ball &newBall, paddle &lPaddle, paddle &rPaddle) {
	tempVel = initVel;
	newBall.reset(lScore + rScore);
	lPaddle.reset();
	rPaddle.reset();
	return 0;
}