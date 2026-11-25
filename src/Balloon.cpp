
#include "Balloon.h"
#include "game.h"

bool Balloon::getExploding() const // explicado en el h
{
	return exploding;
}


bool Balloon::hit(const Rectangle& obj)
{
	if (SceneObject::hit(obj) && !death) // Si me han dado y es la primera vez que me dan
	{

		death = true;
		return true;
	}

	return false;
}
bool Balloon::update(float delta)
{
	constexpr int LimitTime = 6;
	
	this->TextureCol = FrameAnimation;

	if (exploding) // Si he explotado me paro y me animo
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
				//Ponemos por defecto el combo a 1 (para que nos de puntos)
				
				return false;
			}
		}
		else
		{
			TimeAnimation += delta;
		}
		return true;
		
	}
	else
	{
		MobileObject::update(delta);
	}
	return (position.getTopLeftCorner().getY() > -100);

	
}
void Balloon::EscribirDatos(std::ostream& archivo) const
{
	archivo << "Balloon ";
	MobileObject::EscribirDatos(archivo); // Primero los atributos del padre ya que cuando se llama a las constructora primero es la del padre
	archivo <<  " " << FrameAnimation << "\n";

}
Balloon::Balloon(Game* game, std::istream& archivo, Texture* tex, int linea) : MobileObject(game, archivo, tex, linea)
{
	if (!(archivo  >> FrameAnimation) ||  FrameAnimation < 0 || FrameAnimation > 6)
	{
		throw FileFormatError("saved.txt", linea);
	}
	TimeAnimation = 0.0f;
	TimeFrame = 10.0f;
}
Balloon::Balloon(Rectangle pos, int color, Point2D<> velocidad, Texture* textura, Game* game) : MobileObject(velocidad, textura, pos, game)
{


	death = false;
	FrameAnimation = 0;
	TimeAnimation = 0.0f;
	TimeFrame = 10.0f;
	this->texture = this->game->getTexture(this->game->BALLOON); 
}

