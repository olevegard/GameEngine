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
#include <iostream>

#include "Window.h"			// Delta time, average FPS calculation
#include "Renderer.h"			// Delta time, average FPS calculation

#include "Timer.h"			// Delta time, average FPS calculation
#include "Texture.h"		// Regular textures ( Enemy, Player )
#include "Texture_Text.h"	// Text textures ( 'solid', 'blended', 'shaded' ), average FPS display

#include "Enemy.h"
#include "Player.h"

// Setup
bool InitEverything();
bool InitSDL();
bool CreateWindow();
bool CreateRenderer();
void SetupRenderer();
bool SetupTTF( const std::string &fontName ); // Our new function for setting uo SDL_TTF

void InitializeObjects();
void AddEnemies( int32_t count );
void AddEnemy( int32_t height );

// Update ( happens every frame )
void Render();
void RunGame();
void HandleInput();
void UpdateObjects( double delta );

SDL_Rect windowRect = { 0, 0, 600, 800 };
SDL_Point windowMiddle;

Renderer newRenderer;
Window newWindow;

TTF_Font* font;
TTF_Font* bigFont;

bool quit = false;

// Objects
Player player;
Texture background;
Texture topBar;
Texture bottomBar;

Texture_Text fpsCounter;
Texture_Text textSolid;
Texture_Text textShaded;
Texture_Text textBlended;

std::vector< Enemy > enemies;

Timer timer;

int main( int argc, char* args[] )
{
	if ( !InitEverything() )
		return -1;

	InitializeObjects();

	RunGame();

	// Free our fonts
	TTF_CloseFont( font );
	TTF_CloseFont( bigFont );
}
void RunGame()
{
	while ( !quit )
	{
		HandleInput();

		//fpsCounter.RenderValue( renderer, "FPS", timer.GetAverageFPS() );
		double delta = timer.GetDelta();
		UpdateObjects( delta );

		Render();
	}
}

void HandleInput()
{
	SDL_Event event;
	while ( SDL_PollEvent( &event ) )
	{
		if ( event.type == SDL_QUIT )
			quit = true;
		else if ( event.type == SDL_KEYDOWN )
		{
			switch ( event.key.keysym.sym )
			{
				case SDLK_ESCAPE:
					quit = true;
					break;
				case SDLK_RIGHT:
					player.MoveRight( 20 );
					break;
				case SDLK_LEFT:
					player.MoveLeft( 20 );
					break;
				case SDLK_DOWN:
					player.MoveDown( 20 );
					break;
				case SDLK_UP:
					player.MoveUp( 20 );
					break;
				default :
					break;
			}
		}
	}
}
void UpdateObjects( double delta )
{
	player.CheckFinishLine( topBar.GetRect().y + topBar.GetRect().h, windowRect );

	for (  auto &p : enemies )
	{
		p.Update( delta );

		if ( player.CheckCollision( p ) )
			player.ResetPosition( windowRect );

		p.CheckBounds( windowRect );
	}
}
void InitializeObjects()
{
	/*
	textShaded.Init( bigFont, { 255, 0, 255, 255 }, { 0, 0, 255, 255 } );
	textShaded.RenderText_Shaded( renderer, "Shaded" );
	textShaded.CenterAtPoint( windowMiddle );

	textBlended.Init( bigFont, { 255, 255, 0, 255 }, { 0, 0, 255, 255 } );
	textBlended.RenderText_Blended( renderer, "Blended" );
	textBlended.CenterAtPoint( { windowMiddle.x, windowMiddle.y - 160 } );

	textSolid.Init( bigFont, { 255, 255, 255, 255 }, { 0, 0, 0, 255 } ); 
	textSolid.RenderText_Solid( renderer, "Solid" );
	textSolid.CenterAtPoint( { windowMiddle.x, windowMiddle.y + 160 } );
	*/

	background.LoadTexture( newRenderer.renderer, "background_600x800.png" );

	bottomBar.LoadTexture( newRenderer.renderer, "bar_600x40.png" );
	bottomBar.SetPos( { 0, windowRect.h - 40 } );

	topBar.LoadTexture( newRenderer.renderer, "bar_600x40.png" );
	player.LoadTexture( newRenderer.renderer, "player.png" );

	AddEnemies( 15 );
}
void AddEnemies( int32_t count )
{
	int32_t lastEnemyPos = 0;

	for ( int32_t i = 0 ; i < count ; ++i )
	{
		AddEnemy( lastEnemyPos );
		lastEnemyPos += 50;
	}
}
void AddEnemy( int32_t height )
{
	Enemy enemy( { rand() % 300, height, 20, 20 } );
	enemy.LoadTexture( newRenderer.renderer, "enemy.png" );

	if ( ( rand() % 2 ) == 0 )
		enemy.SetSpeed( { 1, 0 } );
	else
		enemy.SetSpeed( { -1, 0 } );

	enemies.push_back( enemy );
}
void Render()
{
	// Clear the window and make it all red
	SDL_RenderClear( newRenderer.renderer );

	newRenderer.RenderTexture( background );

	for (  auto &p : enemies )
		newRenderer.RenderTexture( p );

	newRenderer.RenderTexture( topBar );
	newRenderer.RenderTexture( bottomBar );
	newRenderer.RenderTexture( player );

	// Render the changes above
	SDL_RenderPresent( newRenderer.renderer);
}
// Initialization ++
// ==================================================================
bool InitEverything()
{
	if ( !InitSDL() )
		return false;

	newWindow.CreateWindow( { 0, 0 }, { 600, 800 } );
	newRenderer.Init( newWindow );

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
	bigFont = TTF_OpenFont( fontName.c_str(), 90 );
	
	if ( font == nullptr )
	{
		std::cout << " Failed to load font : " << SDL_GetError() << std::endl;
		return false;
	}

	fpsCounter.Init( font, { 255, 0, 255, 255 }, { 0, 255, 0, 255 } );

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
