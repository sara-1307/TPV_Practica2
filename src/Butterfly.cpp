#include "Butterfly.h"
Butterfly::Butterfly(Point2D<> Dirección, Rectangle pos, Point2D<> velocidad, Texture* textura)
{
	this->Dirección = Dirección; 
	this->position = pos;
	this->Speed = velocidad; 
	this->texture = textura; 

	FrameAnimation = 0;
	TimeAnimation = 0.0f;
	TimeFrame = 10.0f;
	MeMataron = false; 
}
void Butterfly::render() const {
	texture->renderFrame(position.to_sdl(), 1, FrameAnimation);
}


bool Butterfly::update(float delta)
{

	constexpr int LimitTime = 10;

	if (MeMataron) // Si he explotado me paro y me animo
	{

		if (TimeAnimation >= TimeFrame)
		{
			TimeAnimation = 0;
			if (FrameAnimation <= LimitTime)
			{
				FrameAnimation++;
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			TimeAnimation += delta;
		}
		return true;

	}
	position.move(Speed * delta); // Para que el tiempo no dependa de la maquina
	if (position.getTopLeftCorner().getY() < 50 || position.getTopLeftCorner().getY() > 700)
	{
		Dirección.SetY(Dirección.getY() * -1);
	}
	else if (position.getTopLeftCorner().getX() < 50 || position.getTopLeftCorner().getX() > 500)
	{
		Dirección.SetX(Dirección.getX() * -1);
	}
	return true; 

}
