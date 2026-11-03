#include "Bow.h"

Point2D<> Bow::getposmed() // devuelve la posicion del arco para la flecha para crearlo exactamente en el centro
{
	Point2D<> esqui = Position.getTopLeftCorner(); // consigo la esquina
	return Point2D<>(esqui.getX() + Position.getWidth() / 2, esqui.getY() + Position.getHeight() / 2);  // esto hace que se cree justo en la mitad

}
float Bow::GetArrowSpeed() const
{
	return SpeedArrow;
}
void Bow::setArrows(int arrows)
{
	this->NArrow = arrows;
}
void Bow::CrearFlecha()
{
	Point2D posflecha = getposmed();
	Rectangle rec(posflecha, 100, 20);
	Arrow* flecha = new Arrow(this, getTexture(ARROW), rec, Point2D<>(1, 0));
	
}
bool Bow::handleEvent(const SDL_Event& event)  //Como el arco el que se mueve y dispara el es el que recibe y gestiona el input del jugador
{
	if (event.type == SDL_EVENT_KEY_DOWN)
	{
		if (event.key.key == SDLK_UP)
		{
			Address.SetY(-speedBow);
		}
		else if (event.key.key == SDLK_DOWN)
		{
			Address.SetY(speedBow);
		}
		else if (event.key.key == SDLK_LEFT )
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
Bow::Bow(Rectangle pos, Texture* tex, Point2D<> velocidad, int NFlechas, bool armado, int speed)
{
	this->Position = pos; 
	texture = tex;
	this->Address = velocidad;
	this->NArrow = NFlechas; 
	this->armed = armado; 
	this->speedBow = speed;
}
void Bow::render() const
{

	texture->renderFrame(Position.to_sdl(), 0, !armed); //usamo armed porque es un bool es decir en verdad es 1 o 0
}
bool Bow::update(float delta) 
{
	constexpr int limit = 600;
	if (armed)
	{
		LoadTime += delta/1000;
	}
	Rectangle aux = Position.moved(Address * delta);//estoy usando moved no move lo que devuelve un rectangulo

	float y = aux.getTopLeftCorner().getY();

	if (y >= 0 && y + aux.getHeight() <= limit)
	{
		Position = aux;
	}
	return NArrow != 0;
	
}

