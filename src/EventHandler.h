#pragma once
#include <SDL3/SDL_events.h>
class EventHandler
{
public:
	EventHandler();
	void handleEvent(const SDL_Event&);
};

