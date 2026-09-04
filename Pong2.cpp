/*
	Font is Silver by Poppy Works (poppyworks.itch.io.silver)
*/

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <chrono>
#include <iostream>
#include "Vector2.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"
#include "PlayerScore.hpp"

const int kWindowHeight{ 720 };
const int kWindowWidth{ 1280 };
const float kPaddleSpeed{ 1.0f };


//making some enums
enum Buttons
{
	PaddleOneUp = 0,
	PaddleOneDown,
	PaddleTwoUp,
	PaddleTwoDown,
};



//Preset colors
const SDL_Color kSlateBlue{ 0x5B,0x7C,0x99,0xFF };
const SDL_Color kWhite{ 0xF5,0xF5,0xF5 };
//Foward Decleration Function Prototypes
bool init();
bool loadMedia();
void closeDownSDL();
bool checkPaddleColision(Ball const& ball, Paddle const& paddle);

//seeing if this works 
void drawNet();

/* Global SDL Window and Render*/
// These I think should be elsewhere but for just right now. 
SDL_Window* pongWindow{ nullptr };
SDL_Renderer* pongRenderer{ nullptr };
TTF_Font* scoreFont{ nullptr };
// Use an inline function to pass the struct, hopefully this works
static inline void SDL_SetRenderDrawColorStruct(SDL_Renderer* renderer, SDL_Color color) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}
int main()
{
	int exitCode{ 0 };


	//Create the score text fields
	Vector2 pOneScorePos{ kWindowWidth / 4, 20 };
	Vector2 pTwoScorePos{ 3 * kWindowWidth / 4,20 };


	//create the ball
	Ball ball
	(
		Vector2((kWindowWidth / 2.0f) - (kBallWidth / 2.0f),
			(kWindowHeight / 2.0f) - (kBallWidth / 2.0f)),
		Vector2(kBallSpeed, 0.0f)
	
	);
	//create the paddles first vector is position, second is current velocity
	Paddle paddleP1
	(
		Vector2(50.0f, (kWindowHeight / 2.0f) - (kPaddleHeight / 2.0f)),
		Vector2(0.0f, 0.0f));
	Paddle paddleP2
	(
		Vector2(kWindowWidth - 50.0f, (kWindowHeight / 2.0f) - (kPaddleHeight / 2.0f)),
		Vector2(0.0f, 0.0f));

	if (init() == false)
	{
		SDL_Log("Unable to initalize");
		exitCode = 1;
	}
	else
	{

		PlayerScore playerOneScoreText(pOneScorePos, pongRenderer, scoreFont);
		PlayerScore playerTwoScoreText(pTwoScorePos, pongRenderer, scoreFont);

		int pOneScore{ 0 };
		int pTwoScore{ 0 };
		//game logic
		bool isRunning{ true };
		bool buttons[4]{};
		float dt = 0.0f;
		SDL_Event event;
		SDL_zero(event);
		while (isRunning)
		{
			//start counting frame time
			auto startTime = std::chrono::high_resolution_clock::now();


			//There has to be a better way of waiting for input. 
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_EVENT_QUIT)
				{
					SDL_Log("The Window was closed ");
					isRunning = false;
				}
				else if (event.type == SDL_EVENT_KEY_DOWN)
				{

					if (event.key.key == SDLK_ESCAPE)
					{
						SDL_Log("The Window was closed with Escape");
						isRunning = false;
					}
					else if (event.key.key == SDLK_1)
					{
						pOneScore++;
						playerOneScoreText.setScore(pOneScore);
					}
					else if (event.key.key == SDLK_2)
					{
						pTwoScore++;
						playerTwoScoreText.setScore(pTwoScore);
					}
					else if (event.key.key == SDLK_W)
					{
						buttons[Buttons::PaddleOneUp] = true;
					}
					else if (event.key.key == SDLK_S)
					{
						buttons[Buttons::PaddleOneDown] = true;
					}
					else if (event.key.key == SDLK_UP)
					{
						buttons[Buttons::PaddleTwoUp] = true;
					}
					else if (event.key.key == SDLK_DOWN)
					{
						buttons[Buttons::PaddleTwoDown] = true;
					}

				}
				else if (event.type == SDL_EVENT_KEY_UP)
				{
					if (event.key.key == SDLK_W)
					{
						buttons[Buttons::PaddleOneUp] = false;
						
					}
					else if (event.key.key == SDLK_S)
					{
						buttons[Buttons::PaddleOneDown] = false;
					}
					else if (event.key.key == SDLK_UP)
					{
						buttons[Buttons::PaddleTwoUp] = false;
					}
					else if (event.key.key == SDLK_DOWN)
					{
						buttons[Buttons::PaddleTwoDown] = false;
					}

				}
			}

			//setting the speed
			if (buttons[Buttons::PaddleOneUp])
			{
				paddleP1.velocity.y = -kPaddleSpeed;
			}
			else if (buttons[Buttons::PaddleOneDown])
			{
				paddleP1.velocity.y = kPaddleSpeed;
			}
			else
				paddleP1.velocity.y = 0.0f;

			//set speed for p2
			if (buttons[Buttons::PaddleTwoUp])
				paddleP2.velocity.y = -kPaddleSpeed;
			else if (buttons[Buttons::PaddleTwoDown])
				paddleP2.velocity.y = kPaddleSpeed;
			else
				paddleP2.velocity.y = 0.0f;

			paddleP1.Update(dt);
			paddleP2.Update(dt);

			ball.Update(dt);
			
			
			if (checkPaddleColision(ball, paddleP2) || checkPaddleColision(ball,paddleP1))
			{
				ball.velocity.x = -ball.velocity.x;
				
				
			}

			
			SDL_SetRenderDrawColor(pongRenderer, 0x5B, 0x7C, 0x99, 0xFF);
			SDL_RenderClear(pongRenderer);


			//Draws the net
			drawNet();

			//Draw the ball
			ball.Draw(pongRenderer);

			//draw the paddles
			paddleP1.Draw(pongRenderer);
			paddleP2.Draw(pongRenderer);

			//Draw the Score
			playerOneScoreText.Draw();
			playerTwoScoreText.Draw();

			//Present back buffer/renderer
			SDL_RenderPresent(pongRenderer);

			//calculate end time of frame
			auto stopTime = std::chrono::high_resolution_clock::now();
			dt = std::chrono::duration<float, std::chrono::milliseconds::period>(stopTime - startTime).count();

		}

		closeDownSDL();

		return exitCode;

	}
}


	bool init()
	{
		//Initialization flag
		bool success{ true };

		//Initialize SDL
		if (SDL_Init(SDL_INIT_VIDEO) == false)
		{
			SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
			success = false;
		}
		else if (TTF_Init() == false)
		{
			SDL_Log("SDL TTF could not initialize. SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//create our window and renderer
			SDL_CreateWindowAndRenderer("Pong", kWindowWidth, kWindowHeight, 0, &pongWindow, &pongRenderer);
			if (pongWindow == nullptr)
			{
				SDL_Log("Window not created");
				success = false;
			}
			else if (pongRenderer == nullptr)
			{
				SDL_Log("Renderer not created");
				success = false;
			}

			//create the font
			scoreFont = TTF_OpenFont("Silver.ttf", 40);



		}
		return success;
	}

	void closeDownSDL()
	{
		SDL_DestroyRenderer(pongRenderer);
		pongRenderer = nullptr;
		SDL_DestroyWindow(pongWindow);
		pongWindow = nullptr;

		TTF_CloseFont(scoreFont);
		TTF_Quit();
		SDL_Quit();



	}

	void drawNet()
	{
		SDL_SetRenderDrawColorStruct(pongRenderer, kWhite);
		for (int y = 0; y < kWindowHeight; y++)
		{
			if (y % 5)
			{
				SDL_RenderPoint(pongRenderer, kWindowWidth / 2, y);

			}
		}
	}

	bool checkPaddleColision(Ball const& ball, Paddle const& paddle)
	{
		float ballLeft = ball.pos.x;
		float ballRight = ball.pos.x + kBallWidth;
		float ballTop = ball.pos.y;
		float ballBottom = ball.pos.y + kBallHeight;

		float paddleLeft = paddle.pos.x;
		float paddleRight = paddle.pos.x + kPaddleWidth;
		float paddleTop = paddle.pos.y;
		float paddleBottom = paddle.pos.y + kPaddleHeight;


		//SDL_Log(std::to_string(ballLeft).c_str());
		//SDL_Log(std::to_string(paddleLeft).c_str());
		if (ballLeft >= paddleRight)
		{
			return false;
			SDL_Log("false");
		}

		if (ballRight <= paddleLeft)
		{
			return false;
			SDL_Log("false");
		}

		if (ballTop >= paddleBottom)
		{
			return false;
			SDL_Log("false");
		}

		if (ballBottom <= paddleTop)
		{
			return false;
			SDL_Log("false");
		}

		//SDL_Log("true");
		return true;


	}