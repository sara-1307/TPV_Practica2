#include "Vidas.h"
Vidas::Vidas(Texture* tex, Rectangle pos)
{
	textura = tex; 
	this->pos = pos;
}
void Vidas::render() const
{
	textura->renderFrame(pos.to_sdl(), 0, 0);
}
