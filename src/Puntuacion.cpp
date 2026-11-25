#include "Puntuacion.h"
#include "rectangle.h"


Puntuacion::Puntuacion(Game* game, int i)
{
	this->index = i;
	this->game = game;
	this->position = Rectangle(Point2D<>((game->WINDOW_WIDTH - 30) - i * 30, 20), 25, 35);
	this->texture = this->game->getTexture(game->DIGITS);	
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


