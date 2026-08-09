#pragma once
#include <SDL3/sdl.h>
#include "Vector2.hpp"
#include "Ball.hpp"
const int kPaddleWidth = 7;
const int kPaddleHeight = 75;
// gonna try and make this as seperate header and main files
class Paddle {
public:
	Paddle(Vector2 pos,Vector2 velocity);
	void Draw(SDL_Renderer* renderer);
	void Update(float dt);
	Vector2 pos;
	Vector2 velocity;
	SDL_FRect rect{};
	
};