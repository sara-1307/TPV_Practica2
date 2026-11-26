
#include "Balloon.h"




void Balloon::EscribirDatos(std::ostream& archivo) const
{
	archivo << "Balloon ";
	MobileObject::EscribirDatos(archivo); // Primero los atributos del padre ya que cuando se llama a las constructora primero es la del padre
	archivo << " " << color << " " << FrameAnimation << "\n";

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

Balloon::Balloon(Game* game, std::istream& archivo, Texture* tex, int linea) : MobileObject(game, archivo, tex, linea)
{
	if (!(archivo >> color >> FrameAnimation) || color < 0 || color > 7 || FrameAnimation < 0 || FrameAnimation > 6)
	{
		throw FileFormatError("saved.txt", linea);
	}
	TimeAnimation = 0.0f;
	TimeFrame = 10.0f;
}
void Balloon::render() const
{
	texture->renderFrame(position.to_sdl(), color, FrameAnimation);
}
bool Balloon::getexploto() const // explicado en el h
{
	return death;
}

Balloon::Balloon(Rectangle pos, int color, Point2D<> velocidad, Texture* textura, Game* game) : MobileObject(velocidad, textura, pos, game)
{

	this->color = color;
	death = false;
	FrameAnimation = 0;
	TimeAnimation = 0.0f;
	TimeFrame = 10.0f;
}
bool Balloon::update(float delta)
{

	constexpr int LimitTime = 6;

	if (death) // Si he explotado me paro y me animo
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

	return (position.getTopLeftCorner().getY() > -position.getHeight()); // preguntar


}
