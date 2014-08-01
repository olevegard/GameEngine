#include "EventHandler.h"

void EventHandler::Update( )
{
	SDL_Event event;
	while ( SDL_PollEvent( &event ) )
	{
		if ( event.type == SDL_QUIT )
			AddQuitEvent();
		else if ( event.type == SDL_KEYDOWN || event.type == SDL_KEYUP )
			HandleKeyBoard( event );
	}
}
void EventHandler::AddQuitEvent()
{
	events.emplace_back( Event( EventType::Quit ) );
}
void EventHandler::HandleKeyBoard( const SDL_Event &event )
{
	if ( event.type != keyCode[ event.key.keysym.sym ] )
	{
		// Save new state of the button
		keyCode[ event.key.keysym.sym ] = static_cast< SDL_EventType > ( event.type );

		AddKeyboardEvent( event );

		if ( event.key.keysym.sym == SDLK_ESCAPE )
			AddQuitEvent();
	}
}

void EventHandler::AddKeyboardEvent( const SDL_Event &event )
{
	events.push_back( CreateKeyboardEvent( event ) );
}
Event EventHandler::CreateKeyboardEvent( const SDL_Event &event ) const
{
	Event keyEvent( EventType::Keyboard );
	keyEvent.keyboard.key = event.key.keysym.sym; 

	if ( event.type == SDL_KEYUP )
		keyEvent.keyboard.eventType = KeyboardEventType::Released;
	else
		keyEvent.keyboard.eventType = KeyboardEventType::Pressed;

	return keyEvent;
}
std::vector< Event > EventHandler::GetEvents()
{
	return events;
}
void EventHandler::ClearEvents()
{
	//keyPresses.clear();
	events.clear();
}
