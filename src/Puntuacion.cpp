#include "Puntuacion.h"
#include "Puntuacion.h"

Puntuacion::Puntuacion(Texture* tex, Rectangle pos, Game* game) : SceneObject(tex, pos, game)
{

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

bool Puntuacion::update(float delta)
{
	return true;
}

void Puntuacion::Change(int pos)
{
	frame = pos;
}

