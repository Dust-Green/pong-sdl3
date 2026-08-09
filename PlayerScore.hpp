#pragma once
#include "Vector2.hpp"
#include <SDL3/sdl.h>
#include <SDL3_ttf/SDL_ttf.h>
class PlayerScore
{
public:
	PlayerScore(Vector2 pos, SDL_Renderer* renderer, TTF_Font* font);
	~PlayerScore();
	void Draw();
	void setScore(int scoreUpdate);
	

	SDL_Renderer* renderer;
	TTF_Font* font;
	SDL_Surface* surface{};
	SDL_Texture* texture{};
	SDL_FRect rect{};
};