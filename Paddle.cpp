#include "Paddle.hpp"
#include <SDL3/SDL.h>

Paddle::Paddle(Vector2 pos,Vector2 velocity) : pos(pos),velocity(velocity) {
	rect.x = static_cast<int>(pos.x);
	rect.y = static_cast<int>(pos.y);
	rect.w = kPaddleWidth;
	rect.h = kPaddleHeight;
	
}

void Paddle::Draw(SDL_Renderer* renderer)
{
	// we only want the paddle to move up and down 

	//for now at least we might add some horizontal movement as animation.
	rect.y = static_cast<int>(pos.y);
	rect.x = static_cast<int>(pos.x);
	SDL_RenderFillRect(renderer, &rect);
}

void Paddle::Update(float dt)
{
	pos += velocity * dt;
	if (pos.y < 0)
	{
		//Don't go beyond the screen
		pos.y = 0;
	}
	// I'm hard setting the window height at 720 here cause I don't know at this moment 
	// how to share that value from main here. 
	else if (pos.y > (720 - kPaddleHeight))
	{
		//Don't go beyond the bottom of the screen
		pos.y = 720 - kPaddleHeight;
	}
}