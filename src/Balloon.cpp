
#include "Balloon.h"


bool Balloon::hit(const Rectangle& obj)
{
	if (position.hasIntersection(obj)) 
	{
		exploit = true;
		return true;
	}
	 return false;
}
void Balloon::render() const
{
	texture->renderFrame(position.to_sdl(), color, FrameAnimation);
}
bool Balloon::getexploto() const // explicado en el h
{
	return exploit;
}

Balloon::Balloon(Rectangle pos,  int color, Point2D<> velocidad, Texture* textura)
{
	this->position = pos;
	this->color = color; 
	this->Speed = velocidad; 
	this->texture = textura;

	exploit = false;
	FrameAnimation = 0;
	TimeAnimation = 0.0f;
	TimeFrame = 10.0f;
}
bool Balloon::update(float delta)
{
	
	constexpr int LimitTime = 6;

	if (exploit) // Si he explotado me paro y me animo
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
	return (position.getTopLeftCorner().getY() > -50); // preguntar

	
}
