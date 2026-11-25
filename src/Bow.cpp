#include "Bow.h"
#include "game.h"
#include "rectangle.h"

Point2D<> Bow::getMediumPos() // devuelve la posicion del arco para la flecha para crearlo exactamente en el centro
{
	Point2D<> esqui = position.getTopLeftCorner(); // consigo la esquina
	return Point2D<>(esqui.getX() + position.getWidth() / 2, esqui.getY() + position.getHeight() / 2);  // esto hace que se creme justo en la mitad

}
void Bow::EscribirDatos(std::ostream& archivo) const
{
	archivo << "Bow ";
	SceneObject::EscribirDatos(archivo);

	archivo << Address.getX() << " " << Address.getY() << " " << speed.getX() << " " << speed.getY() << " " << NArrow << " " << armed << "\n";
}
Bow::Bow(Game* game, std::istream& archivo, Texture* tex, int linea): SceneObject(game, archivo, tex, linea)
{
	float x, y, sx, sy;
	int a, ar;

	if (!(archivo >> x >> y >> sx >> sy >> a >> ar) || a < 0 || (ar != 0 && ar != 1))
	{
		throw FileFormatError("saved.txt", linea);
	}

	Address.SetX(x);
	Address.SetY(y);

	speed.SetX(sx);
	speed.SetY(sy);

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

Bow::Bow(Rectangle pos, Texture* tex, Point2D<> speed, int NFlechas, bool armado, Point2D<> Address, Game* game) :SceneObject(tex, pos, game)
{

	this->Address = Address;
	this->NArrow = NFlechas;
	this->armed = armado;
	this->speed = speed;
	LoadTime = 0.0f;
	SpeedArrow = 0.3f;

}
bool Bow::handleEvent(const SDL_Event& event)  //Como el arco el que se mueve y dispara el es el que recibe y gestiona el input del jugador
{
	
	if (event.type == SDL_EVENT_KEY_DOWN)
	{
		//Controlamos si se esta presionando el control para "tensar" el arco
		charging = event.key.key == SDLK_RCTRL || event.key.mod & SDL_KMOD_CTRL;
		//Revisamos las teclas
		if (event.key.key == SDLK_UP)
		{
			speed.SetY(-BowSpeed);
		}
		else if (event.key.key == SDLK_DOWN)
		{
			speed.SetY(BowSpeed);
		}
		else if (event.key.key == SDLK_LEFT )
		{
			//charging = event.key.mod & SDL_KMOD_CTRL;
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
				if (SpeedArrow > SpeedMax)
				{
					SpeedArrow = SpeedMax;
				}
				else if (SpeedArrow < SpeedMin)
				{
					SpeedArrow = SpeedMin;
				}
				NArrow--;
				armed = false;
				this->game->addObject(new Arrow(this->game, this->game->getTexture(Game::ARROW), Rectangle(this->getMediumPos(), 40, 10), Point2D<>(SpeedArrow, 0)));
				
				return true;
			}
		}
		
	}
	else if (event.type == SDL_EVENT_KEY_UP)
	{
		//Frenamos la carga y el arco
		charging = false;
		speed.SetY(0);
	}
	return false;
}

int Bow::getArrows()
{
	return NArrow;
}
bool Bow::update(float delta) 
{
	constexpr int limit = 600;
	this->TextureCol = !armed;
	if (armed && charging)
	{
		SpeedArrow += delta / 1000;
	}
	else
	{
		SpeedArrow = SpeedMin;

	}
	//Guardamos la posición antes de mover
	Rectangle aux = this->position;
	//Movemos con el update del padre
	
	//Calculamos si nos salimos de los límites, y si es así volvemos a antes de movernos.
	float y = this->position.getTopLeftCorner().getY();
	if (y <= 0 || y > this->game->WINDOW_HEIGHT-50)
	{
		this->position = aux;
	}


	return NArrow != 0;
	
}
