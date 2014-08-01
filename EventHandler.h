#pragma once

#include <vector>
#include <map>

#include <SDL2/SDL.h>

// Event structures
// Notes :
// 		The struvture of the events might seem siilar to those of SLD_Event, but theere are some differences:
// 			1. Simpler
// 			2. Code is freely avaible and easy to modify
// 			3. Every enumeration is a stored as enum class, so you can't use the wrong enum value or implicitly convert to int
//
// Buttons ( keyboard, mouse, joystick )
enum class ButtonEventType
{
	Pressed,
	Released,
};
enum class ButtonState
{
	Up,
	Down,
};
// Keyboard
struct KeyboardEvent
{
	ButtonEventType eventType;
	SDL_Keycode key;
};
// Mouse
enum class MouseButton
{
	Left,
	Middle,
	Right,
};
struct MouseMotionEvent
{
	SDL_Point newPos;
	SDL_Point relativePos;
};
struct MouseButtonEvent
{
	ButtonEventType eventType;
	MouseButton button;
};
// Main event class
enum class EventType
{
	Keyboard,
	Mouse,
	Quit
};
struct Event
{
	Event( EventType type_ )
		:	type( type_ )
	{
	}
	EventType type;

	// Event Types
	KeyboardEvent keyboard;
	MouseMotionEvent mouse;
};
class EventHandler
{
	public:

	void Update( );

	void ClearEvents();
	std::vector< Event > GetEvents();

	ButtonState GetKeyState( SDL_Keycode key ) const;
	bool IsKeyDown( SDL_Keycode key ) const;

	private:
	void HandleKeyBoard( const SDL_Event &event );
	void HandleMouse( const SDL_Event &event );

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
	std::map< int8_t, int8_t > mouseButton;
};

