#pragma once

#include <vector>
#include <map>

#include <SDL2/SDL.h>

// Event handling
enum class EventType
{
	Keyboard,
	Mouse,
	Quit
};
enum class KeyboardEventType
{
	Pressed,
	Released,
};
enum class KeyboardKeyState
{
	Up,
	Down,
};
struct KeyboardEvent
{
	KeyboardEventType eventType;
	SDL_Keycode key;
};
struct Event
{
	Event( EventType type_ )
		:	type( type_ )
	{
	}
	EventType type;
	KeyboardEvent keyboard;
};
class EventHandler
{
	public:

	void Update( );

	void ClearEvents();
	std::vector< Event > GetEvents();

	KeyboardKeyState GetKeyState( SDL_Keycode key ) const;
	bool IsKeyDown( SDL_Keycode key ) const;

	private:
	void HandleKeyBoard( const SDL_Event &event );

	void AddQuitEvent();
	void AddKeyboardEvent( const SDL_Event &event );
	Event CreateKeyboardEvent( const SDL_Event &event ) const;

	// Only holds key press events for this frame
	// I.E. if a button was pressed or released this frame
	// It will not contain button states that was the same in the previous event
	// So if you hold the button down then release it, only the first press and release will register
	//std::vector< KeyPressEvent > keyPresses;
	std::vector< Event > events;

	// Holds the current state of every button
	std::map< SDL_Keycode, SDL_EventType > keyCode;
};

