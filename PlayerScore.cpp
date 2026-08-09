#include "PlayerScore.hpp"
#include "Vector2.hpp"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <string>

PlayerScore::PlayerScore(Vector2 pos, SDL_Renderer* renderer, TTF_Font* font)
	: renderer(renderer),font(font)
{
	surface = TTF_RenderText_Solid(font, "0",3, { 0xFF,0xFF,0xFF,0xFF });
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	float width, height;
	SDL_GetTextureSize(texture, &width, &height);
	

	rect.x = (pos.x);
	rect.y = (pos.y);
	rect.w = width;
	rect.h = height;
}

PlayerScore::~PlayerScore()
{
	SDL_DestroySurface(surface);
	SDL_DestroyTexture(texture);
}

void PlayerScore::Draw()
{
	SDL_RenderTexture(renderer, texture, nullptr, &rect);
}
void PlayerScore::setScore(int scoreUpdate)
{
	SDL_DestroySurface(surface);
	SDL_DestroyTexture(texture);

	surface = TTF_RenderText_Solid(font, std::to_string(scoreUpdate).c_str(), 2, {0xFF,0xFF,0xFF,0xFF});
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	float width, height; 
	SDL_GetTextureSize(texture, &width, &height);
	rect.w = width;
	rect.h = height;
}