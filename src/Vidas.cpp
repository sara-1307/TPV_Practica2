#include "Vidas.h"

Vidas::Vidas(Texture* tex, Rectangle pos, Game* game) : SceneObject(tex, pos, game)
{

}
void Vidas::render() const
{
	texture->renderFrame(position.to_sdl(), 0, 0);
}

bool Vidas::update(float delta)
{
	return true;
}
