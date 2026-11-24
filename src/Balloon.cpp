
#include "Balloon.h"
#include "game.h"

bool Balloon::getExploding() const // explicado en el h
{
	return exploding;
}
//Balloon::Balloon(Game* game)
//{
//	
//	//LLamamaos al constructor de mobile object para configurar su velocidad
//	//Pasamos un puntero al randomizador del game, es necesario que sea un puntero porque si creamos un randomizador nuevo, tendriamos que meterle
//	//lo de los numeros y consumiramos mucho, es necesario que sea un puntero para que sea el randomizador del game
//	this->game = game;
//	this->Combo = 0;
//	this->HitObject = nullptr;
//	this->balspeed = game->getbalspeed();
//	std::mt19937_64* randomGenerator = (this->game->GetRandomGenerator());
//	this->TextureFil = std::uniform_int_distribution<int>(0, 5)(*randomGenerator);
//	this->speed = Vector2D<float>(0, std::uniform_real_distribution<float>(-1*this->balspeed, 0.3*this->balspeed)(*randomGenerator));
//	int posx = std::uniform_int_distribution<int>(300, 700)(*randomGenerator);
//	this->position = Rectangle(Point2D<>(posx, 800), 100, 100);
//	this->texture = this->game->getTexture(this->game->BALLOON); mantener
//
//	exploding = false;
//	FrameAnimation = 0;
//	TimeAnimation = 0.0f;
//	TimeFrame = 10.0f;
//	this->game->CreateObjects(this);
//}

bool Balloon::hit(const Rectangle& obj, SceneObject* atacante)
{
	if (SceneObject::hit(obj, atacante) && !death) // Si me han dado y es la primera vez que me dan
	{

		death = true;
		atacante->explotados(); // hago que el contador del atacante suba
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
				this->game->addPoints(this->game->getBalPoints()*Combo);
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

//void Balloon::saveObj(std::ostream& output)
//{
//	output << "Balloon ";
//	MobileObject::saveObj(output);
//	//Guardamos el estado del globo
//	output <<this->exploding <<" "<<this->Combo << std::endl;
//}
//
//Balloon::Balloon(Game* game, std::ifstream &input)
//{
//	this->game = game;
//	//Lectura coordenadas
//	float x, y;
//	input >> x >> y;
//	this->position = Rectangle(Point2D<>(x, y), 100, 100);
//	//Lectura textura
//	int fil, col;
//	input >> fil >> col;
//	
//	this->TextureFil = fil;
//	this->TextureCol = col;
//	this->texture = this->game->getTexture(this->game->BALLOON);
//	//Lectura velocidad
//	input >> x >> y;
//	this->speed = Vector2D<float>(x, y);
//	//Carga de estado
//	int exploding;
//	input >> exploding;
//	this->exploding = exploding;
//	input >> this->Combo;
//
//	FrameAnimation = 0;
//	TimeAnimation = 0.0f;
//	TimeFrame = 10.0f;
//	this->game->CreateObjects(this);
//}
