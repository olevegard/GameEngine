#include "EventHandler.h"

void EventHandler::HandleKeyBoard( const SDL_Event &event )
{
	if ( event.type != keyCode[ event.key.keysym.sym ] )
	{
		// Save new state of the button
		keyCode[ event.key.keysym.sym ] = static_cast< SDL_EventType > ( event.type );

		AddKeyPressEvent( event );
	}
}
void EventHandler::AddKeyPressEvent( const SDL_Event &event )
{
	keyPresses.push_back( CreateKeyPressEvent( event ) );;
}
KeyPressEvent EventHandler::CreateKeyPressEvent( const SDL_Event &event ) const
{
	KeyPressEvent keyEvent;
	keyEvent.key = event.key.keysym.sym; 

	if ( event.type == SDL_KEYUP )
		keyEvent.type = KeyPressEventType::Released;
	else
		keyEvent.type = KeyPressEventType::Pressed;

	return keyEvent;
}
