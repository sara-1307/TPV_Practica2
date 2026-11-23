#include "Vidas.h"
#include "rectangle.h"

Vidas::Vidas(Game* game,int i)
{
	this->ArrowIndex = i;
	this->game = game;
	this->texture = this->game->getTexture(this->game->ARROW);
	this->position = Rectangle(Point2D<>(20 + i * 35, 20), 30, 30);
}

void Vidas::render() const
{
	if (game->getArrows() > ArrowIndex)
	{
		SceneObject::render();
	}
}


bool Vidas::update(float delta)
{
	return true;
}
