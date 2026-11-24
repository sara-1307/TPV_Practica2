#pragma once
#include <fstream>
//Rs
class Game;
class GameObject
{
protected:
	Game* game;
public:
	virtual void render() const = 0;
	virtual bool update(float delta) = 0;
	GameObject(Game* game);
	virtual void EscribirDatos(std::ostream& archivo) const = 0;
	virtual ~GameObject() = default;
};
