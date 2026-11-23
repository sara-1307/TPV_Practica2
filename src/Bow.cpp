#include "Bow.h"
#include "game.h"
#include "rectangle.h"

Point2D<> Bow::getMediumPos() // devuelve la posicion del arco para la flecha para crearlo exactamente en el centro
{
	Point2D<> esqui = position.getTopLeftCorner(); // consigo la esquina
	return Point2D<>(esqui.getX() + position.getWidth() / 2, esqui.getY() + position.getHeight() / 2);  // esto hace que se cree justo en la mitad

}
float Bow::GetArrowSpeed() const
{
	return SpeedArrow;
}
void Bow::setArrows(int arrows)
{
	this->NArrow = arrows;
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
				new Arrow(this->game, this->getMediumPos(),SpeedArrow);
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
Bow::Bow(Game* game,int BowMovSpeed, int NFlechas)
{
	this->armed = false;
	this->charging = false;
	this->game = game;
	this->position = Rectangle(Point2D<>(100, 100), 100, 100);
	this->texture = game->getTexture(game->BOW);
	this->BowSpeed = BowMovSpeed;
	this->NArrow = NFlechas; 
	this->game->CreateObjects(this);

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
	MobileObject::update(delta);
	//Calculamos si nos salimos de los límites, y si es así volvemos a antes de movernos.
	float y = this->position.getTopLeftCorner().getY();
	if (y <= 0 || y > this->game->WINDOW_HEIGHT-50)
	{
		this->position = aux;
	}


	return NArrow != 0;
	
}
void Bow::saveObj(std::ostream& output)
{
	output << "Bow ";
	MobileObject::saveObj(output);
	output <<this->NArrow << " " << this->BowSpeed << " " << this->armed << endl;
}
Bow::Bow(Game* game, std::ifstream& input)
{
	this->game = game;
	this->charging = false;
	//Lectura coordenadas
	float x, y;
	input >> x >> y;
	this->position = Rectangle(Point2D<>(x, y), 100, 100);
	//Lectura textura
	int fil, col;
	input >> fil >> col;
	this->TextureFil = fil;
	this->TextureCol = col;
	this->texture = this->game->getTexture(this->game->BOW);
	//Lectura velocidad
	input >> x >> y;
	this->speed = Vector2D<float>(x, y);

	input >> this->NArrow >> this->BowSpeed >> this->armed;
	this->game->CreateObjects(this);
	
}
