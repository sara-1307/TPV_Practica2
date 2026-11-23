#pragma once
class Game;
class GameObject
{
protected:
	Game* game;
public:
	virtual void render() const = 0;
	virtual bool update(float delta) = 0;
};
