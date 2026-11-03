#include "Puntuacion.h"

Puntuacion::Puntuacion(Texture* tex, Rectangle pos)
{
	texture = tex;
	this->position = pos;
	frame = 0;
}
void Puntuacion::render() const
{
	texture->renderFrame(position.to_sdl(), 0, frame);
}

void Puntuacion::update(int pos)
{
	Change(pos); //Me parecia muy violento hacer que el update cambiara el fram asi que hice una funcion auxiliar.
}
void Puntuacion::Change(int pos)
{
	frame = pos;
}

