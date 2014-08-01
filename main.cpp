// SLD2 Tutorial Part 10 - Headerphile.blogspot.no
// Text renderering
// Extends our game by adding text
// Compile  : clang++ main.cpp Texture.cpp Teure_Text.cpp Timer.cpp -std=c++1y -lSDL2 -lSDL2_image -lSDL2_ttf -o Game
// Run      : ./Game
// Updated : Texture.h/.cpp, Texture_Text.h/.cpp, Timer.h/.cpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <vector>
#include <map>
#include <iostream>

//#include "Timer.h"			// Delta time, average FPS calculation
#include "Texture.h"		// Regular textures ( Enemy, Player )
//#include "Texture_Text.h"	// Text textures ( 'solid', 'blended', 'shaded' ), average FPS display

//#include "Enemy.h"
//#include "Player.h"

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

// Event handling
enum class KeyPressEventType
{
	Pressed,
	Released,
};

struct KeyPressEvent
{
	KeyPressEventType type;
	SDL_Keycode key;
};

// Holds the current state of every button
// For the actual key press or release event, see below
std::map< SDL_Keycode, SDL_EventType > keyCode;

// Only holds key press events for this frame
// I.E. if a button was pressed or released this frame
// It will not contain button states that was the same in the previous event
// So if you hold the button down then release it, only the first press and release will register
std::vector< KeyPressEvent > keyPresses;

void HandleKeyBoard( const SDL_Event &event );
void AddKeyPressEvent( const SDL_Event &event );
KeyPressEvent CreateKeyPressEvent( const SDL_Event &event );

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
		HandleInput();

		Render();

		for ( const auto &event : keyPresses )
		{
			std::cout << "Button with ID : " << event.key << " was : ";

			if ( event.type == KeyPressEventType::Pressed )
				std::cout << "Pressed\n";
			else
				std::cout << "Released\n";
		}

		keyPresses.clear();
	}
}

void HandleInput()
{
	SDL_Event event;
	while ( SDL_PollEvent( &event ) )
	{
		if ( event.type == SDL_QUIT )
			quit = true;
		else if ( event.type == SDL_KEYDOWN || event.type == SDL_KEYUP )
		{
			HandleKeyBoard( event );
			switch ( event.key.keysym.sym )
			{
				case SDLK_ESCAPE:
					quit = true;
					break;
			}
		}
	}
}
KeyPressEvent CreateKeyPressEvent( const SDL_Event &event )
{
	KeyPressEvent keyEvent;
	keyEvent.key = event.key.keysym.sym; 

	if ( event.type == SDL_KEYUP )
		keyEvent.type = KeyPressEventType::Released;
	else
		keyEvent.type = KeyPressEventType::Pressed;

	return keyEvent;
}
void AddKeyPressEvent( const SDL_Event &event )
{
	keyPresses.push_back( CreateKeyPressEvent( event ) );;
}
void HandleKeyBoard( const SDL_Event &event )
{
	if ( event.type != keyCode[ event.key.keysym.sym ] )
	{
		// Save new state of the button
		keyCode[ event.key.keysym.sym ] = static_cast< SDL_EventType > ( event.type );

		AddKeyPressEvent( event );
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
