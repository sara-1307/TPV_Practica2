#include "Puntuacion.h"
#include "rectangle.h"


Puntuacion::Puntuacion(Game* game, int i)
	: SceneObject(
		game->getTexture(game->DIGITS),
		Rectangle(
			Point2D<>((game->WINDOW_WIDTH - 30) - i * 30, 20),
			25, 35
		),
		game
	)
{
	this->index = i;
}
void Puntuacion::render() const
{
	SceneObject::render();
}
int Puntuacion::getDigit()
{
	int goal = game->getPoint();
	int aux = goal % 10;
	goal = goal / 10;
	for (int i = 0; i < this->index; i++)
	{
		aux = goal % 10;
		goal = goal / 10;
	}
	return aux;
}

bool Puntuacion::update(float delta)
{
	this->TextureCol = getDigit();
	return true;
}


