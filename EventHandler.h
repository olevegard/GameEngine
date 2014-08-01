#pragma once

#include <vector>
#include <map>

#include <SDL2/SDL.h>

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

class EventHandler
{
	public:
	void HandleKeyBoard( const SDL_Event &event );

	std::vector< KeyPressEvent > GetKeyPresses() const
	{
		return keyPresses;
	}
	void ClearEvents()
	{
		keyPresses.clear();
	}

	private:
	// Holds the current state of every button
	// For the actual key press or release event, see below
	std::map< SDL_Keycode, SDL_EventType > keyCode;

	// Only holds key press events for this frame
	// I.E. if a button was pressed or released this frame
	// It will not contain button states that was the same in the previous event
	// So if you hold the button down then release it, only the first press and release will register
	std::vector< KeyPressEvent > keyPresses;

	void AddKeyPressEvent( const SDL_Event &event );
	KeyPressEvent CreateKeyPressEvent( const SDL_Event &event ) const;
};

