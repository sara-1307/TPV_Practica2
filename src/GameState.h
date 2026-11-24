#pragma once
#include <list>
//#include <SDL3/SDL_events.h>
#include "GameObject.h"
#include "game.h"
#include "EventHandler.h"
class GameState
{

protected:
	Game* game;
	list <GameObject*> gameObjectList;
	list<EventHandler*> eventHandlerList;


public:

	GameState(Game* game);
	virtual void render() const;
	virtual bool update(float delta);
	virtual void handleEvent(const SDL_Event&);
	Game* getGame() const;


};

