#include "Dance.h"
Dance::Dance(Texture* tex, Rectangle pos)
{
	this->texture = tex;
	this->position = pos;

}
Dance::Dance()
{
	texture = nullptr;
}
void Dance::render() const
{
	texture->renderFrame(position.to_sdl(), 0, frame); 
}
bool Dance::update(float delta)
{
	constexpr int limit = 8;
	TimeAnimation += delta;
	if (TimeAnimation >= TimeFrame)
	{
		TimeAnimation -= TimeFrame;
		if (frame < limit)
		{
			frame++;
			return true;
		}
		else
		{
				frame = 0;
				return true;

			
		}
	}
	return true;
}

