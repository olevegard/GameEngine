// SLD2 Tutorial Part 10 - Headerphile.blogspot.no
// Text renderering
// Extends our game by adding text
// Compile  : clang++ main.cpp Texture.cpp Teure_Text.cpp Timer.cpp -std=c++1y -lSDL2 -lSDL2_image -lSDL2_ttf -o Game
// Run      : ./Game
// Updated : Texture.h/.cpp, Texture_Text.h/.cpp, Timer.h/.cpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <vector>

#include "Texture.h"
#include "EventHandler.h"

// Setup
bool InitEverything();
bool InitSDL();
bool CreateWindow();
bool CreateRenderer();
void SetupRenderer();
bool SetupTTF( const std::string &fontName ); // Our new function for setting uo SDL_TTF


void InitializeObjects();
// Update ( happens every frame )
//
void Render();
void RunGame();
void HandleInput();

SDL_Rect windowRect = { 900, 300, 600, 800 };
SDL_Point windowMiddle;

SDL_Window* window;
SDL_Renderer* renderer;

TTF_Font* font;

bool quit = false;

// Objects
Texture background;
Texture object;

EventHandler input;

int main( int argc, char* args[] )
{
	if ( !InitEverything() )
		return -1;

	InitializeObjects();

	RunGame();

	// Free our fonts
	TTF_CloseFont( font );
}
void RunGame()
{
	while ( !quit )
	{
		input.Update( );

		Render();

		for ( const auto &event : input.GetEvents() )
		{
			if ( event.type == EventType::Keyboard )
			{
				if ( event.keyboard.key == SDLK_LEFT )
				{
					std::cout << "Left : ";
					if ( event.keyboard.eventType == ButtonEventType::Pressed )
						std::cout << " prssed\n";
					else
						std::cout << " released\n";
				}
			}
			else if ( event.type == EventType::Quit )
				quit = true;
			else if ( event.type == EventType::MouseButton )
			{
				if ( event.mouseButton.button == MouseButton::Left )
				{
					std::cout << "Left mosue button : ";
					if ( event.mouseButton.eventType == ButtonEventType::Pressed )
						std::cout << "pressed\n";
					else
						std::cout << "released\n";
				}
			}
		}
		if ( input.IsKeyDown( SDLK_RIGHT )  )
			std::cout << time(NULL) << " right is down\n";

		if ( input.IsMouseButtonDown( MouseButton::Right )  )
			std::cout << time(NULL) << " right is down\n";
		input.ClearEvents();
	}
}
void InitializeObjects()
{
	background.LoadTexture( renderer, "background.png" );
}
void Render()
{
	// Clear the window and make it all red
	SDL_RenderClear( renderer );

	background.Render( renderer );

	SDL_RenderPresent( renderer);
}
// Initialization ++
// ==================================================================
bool InitEverything()
{
	if ( !InitSDL() )
		return false;

	if ( !CreateWindow() )
		return false;

	if ( !CreateRenderer() )
		return false;

	if ( !SetupTTF( "sketchy.ttf" ) )
		return false;

	SetupRenderer();
	windowMiddle.x = static_cast< uint32_t > ( windowRect.w * 0.5 );
	windowMiddle.y = static_cast< uint32_t > ( windowRect.h * 0.5 );

	return true;
}
bool SetupTTF( const std::string &fontName)
{
	if ( TTF_Init() == -1 )
	{
		std::cout << " Failed to initialize TTF : " << SDL_GetError() << std::endl;
		return false;
	}

	font = TTF_OpenFont( fontName.c_str(), 38 );

	if ( font == nullptr )
	{
		std::cout << " Failed to load font : " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}
bool InitSDL()
{
	if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
	{
		std::cout << " Failed to initialize SDL : " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}
bool CreateWindow()
{
	window = SDL_CreateWindow( "Server", windowRect.x, windowRect.y, windowRect.w, windowRect.h, 0 );

	if ( window == nullptr )
	{
		std::cout << "Failed to create window : " << SDL_GetError();
		return false;
	}

	return true;
}
bool CreateRenderer()
{
	renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );

	if ( renderer == nullptr )
	{
		std::cout << "Failed to create renderer : " << SDL_GetError();
		return false;
	}

	return true;
}
void SetupRenderer()
{
	// Set size of renderer to the same as window
	SDL_RenderSetLogicalSize( renderer, windowRect.w, windowRect.h );

	// Set color of renderer to red
	SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
}
