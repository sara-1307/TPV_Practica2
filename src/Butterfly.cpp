#include "Butterfly.h"
#include "game.h"

Butterfly::Butterfly(Point2D<> Dirección, Rectangle pos, Point2D<> velocidad, Texture* textura, float limirdir, Game* game)
	: MobileObject(velocidad, textura, pos, game)
{

	this->Dirección = Dirección;
	FrameAnimation = 0;
	TimeAnimation = 0.0f;
	TimeFrame = 10.0f;
	death = false;
	this->limitdir = limirdir;
	mismadir = 0;

}
bool Butterfly::hit(const Rectangle& obj)
{
	if (SceneObject::hit(obj) && !death)
	{

		death = true;
       return true;
	}

	return false;
}
void Butterfly::render() const {
	texture->renderFrame(position.to_sdl(), 0, FrameAnimation);
}

Butterfly::Butterfly(Game* game, std::istream& archivo,
	Texture* tex, int linea)
	: MobileObject(game, archivo, tex, linea)
{
	TimeAnimation = 0.0f;
	TimeFrame = 10.0f;

	float x, y, f;
	int fa;

	if (!(archivo >> x >> y >> f >> fa))
	{
		throw FileFormatError("saved.txt", linea);
	}

	if (fa < 0 || fa > 11)
	{
		throw FileFormatError("saved.txt", linea);
	}

	Dirección.SetX(x);
	Dirección.SetY(y);
	mismadir = f;
	FrameAnimation = fa;
}
void Butterfly::EscribirDatos(std::ostream& archivo) const
{

	archivo << "Butterfly ";
	MobileObject::EscribirDatos(archivo);

	archivo << " " << Dirección.getX() << " " << Dirección.getY() << "  " << mismadir << " " << FrameAnimation << " " << "\n";

}
bool Butterfly::update(float delta)
{

	constexpr int LimitTime = 10;
	constexpr float velocidaddemuerte = 0.5f;



	if (TimeAnimation >= TimeFrame)
	{
		TimeAnimation = 0;
		if (FrameAnimation <= LimitTime)
		{
			FrameAnimation++;

		}
		else
		{
			FrameAnimation = 0;
		}
	}
	else
	{
		TimeAnimation += delta;
	}


	if (death) // Si me muero para abajo
	{

		Speed.SetX(0);
		Speed.SetY(velocidaddemuerte);
		position.move(Speed * delta);
		if (position.getTopLeftCorner().getY() > Game::WINDOW_HEIGHT) // Solo me puedo morir si me han dado 
		{
			game->Quitarpuntuación(10);
			return false;
		}
		return true;

	}



	if (mismadir >= limitdir) // Si ya ha pasado mi tiempo de moverme por esa misma dir me cambio a una dir aleatoria 
	{
		int x = game->nuevadir();
		int y = game->nuevadir();
		mismadir = 0;
		Speed.SetX(x * 0.15f);
		Speed.SetY(y * 0.15f);
	}


	mismadir += delta;


	if (position.getTopLeftCorner().getY() < 10 || position.getTopLeftCorner().getY() + position.getHeight() > Game::WINDOW_HEIGHT - position.getHeight())
	{

		Speed.SetY(Speed.getY() * -1);
	}
	if (position.getTopLeftCorner().getX() < 10 || position.getTopLeftCorner().getX() + position.getWidth() > Game::WINDOW_WIDTH - position.getWidth())
	{

		Speed.SetX(Speed.getX() * -1);
	}
	position.move(Speed * delta);

	return true;

}
