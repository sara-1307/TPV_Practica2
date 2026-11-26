#include "Bow.h"
#include "game.h"

Point2D<> Bow::getposmed()
{
	Point2D<> esqui = position.getTopLeftCorner();

	return Point2D<>(esqui.getX() + position.getWidth() / 2, esqui.getY() + position.getHeight() / 2);
}

void Bow::EscribirDatos(std::ostream& archivo) const
{
	archivo << "Bow ";
	SceneObject::EscribirDatos(archivo);

	archivo << Address.getX() << " " << Address.getY() << " " << Speed.getX() << " " << Speed.getY() << " " << NArrow << " " << armed << "\n";
}
Bow::Bow(Game* game, std::istream& archivo, Texture* tex, int linea)
	: SceneObject(game, archivo, tex, linea)
{
	float x, y, sx, sy;
	int a, ar;

	if (!(archivo >> x >> y >> sx >> sy >> a >> ar) || a < 0 || (ar != 0 && ar != 1))
	{
		throw FileFormatError("saved.txt", linea);
	}

	Address.SetX(x);
	Address.SetY(y);

	Speed.SetX(sx);
	Speed.SetY(sy);

	NArrow = a;
	armed = (ar != 0);
	LoadTime = 0.0f;
	SpeedArrow = 1.0f;
}
float Bow::GetArrowSpeed() const
{
	return SpeedArrow;
}
void Bow::setArrows(int arrows)
{
	this->NArrow = arrows;
}
Arrow* Bow::CrearFlecha()
{

	Rectangle rec(getposmed(), 100, 20);
	return  new Arrow(game, game->getTexture(Game::ARROW), rec, Point2D<>(SpeedArrow, 0));


}
bool Bow::handleEvent(const SDL_Event& event)  //Como el arco el que se mueve y dispara el es el que recibe y gestiona el input del jugador
{
	float mouseX, mouseY;
	SDL_MouseButtonFlags flags = SDL_GetMouseState(&mouseX, &mouseY);

	if (event.type == SDL_EVENT_KEY_DOWN)
	{
		if (event.key.key == SDLK_UP)
		{
			Address.SetY(-Speed.getY());
		}
		else if (event.key.key == SDLK_DOWN)
		{
			Address.SetY(Speed.getY());
		}
		else if (event.key.key == SDLK_LEFT)
		{
			if (!armed && NArrow != 0)
			{
				armed = true;
				LoadTime = 0;
			}
		}
		else if (event.key.key == SDLK_RIGHT)
		{
			if (armed && NArrow != 0)
			{

				armed = false;
				game->addObject(CrearFlecha());
				NArrow--;
				return true;
			}
		}

	}
	else if (event.type == SDL_EVENT_KEY_UP)
	{
		Address.SetY(0);
	}
	return false;
}
Bow::Bow(Rectangle pos, Texture* tex, Point2D<> speed, int NFlechas, bool armado, Point2D<> Address, Game* game) :SceneObject(tex, pos, game)
{

	this->Address = Address;
	this->NArrow = NFlechas;
	this->armed = armado;
	this->Speed = speed;
	LoadTime = 0.0f;
	SpeedArrow = 0.3f;

}
void Bow::render() const
{

	texture->renderFrame(position.to_sdl(), 0, !armed); //usamo armed porque es un bool es decir en verdad es 1 o 0
}
bool Bow::update(float delta)
{
	constexpr int limit = 600;

	Rectangle aux = position.moved(Address * delta);//estoy usando moved no move lo que devuelve un rectangulo

	float y = aux.getTopLeftCorner().getY();

	if (y >= 0 && y + aux.getHeight() <= limit)
	{
		position = aux;
	}
	return NArrow != 0;

}

