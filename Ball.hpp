#pragma once
#include "Vector2.hpp"
#include <SDL3/sdl.h>
#include <SDL3/SDL_render.h>

const int kBallWidth = 15;
const int kBallHeight = 15;

class Ball
{
public:

	Vector2 pos;
	SDL_FRect rect{};
	Vector2 velocity;
	Ball(Vector2 pos,Vector2 velocity)
		:pos(pos), velocity(velocity)
	{
		rect.x = static_cast<int>(pos.x);
		rect.y = static_cast<int>(pos.y);

		rect.w = kBallWidth;
		rect.h = kBallHeight;
	}
	void Update(float dt)
	{
		pos += velocity * dt;
	}

	//Apparently we would ideally want to keep the renderer out of Ball but for Pong we're gonna do it
	// Research how to keep it seperate later. 
	void Draw(SDL_Renderer* renderer)
	{
		rect.x = static_cast<int>(pos.x);
		rect.y = static_cast<int>(pos.y);

		SDL_RenderFillRect(renderer, &rect);

	}

	
};