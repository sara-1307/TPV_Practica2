#include "Vidas.h"
#include "rectangle.h"

Vidas::Vidas(Game* game, int i)
	: SceneObject(game->getTexture(game->ARROW),
		Rectangle(Point2D<>(20 + i * 35, 20), 30, 30),
		game)
{
	this->ArrowIndex = i;
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
