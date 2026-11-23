
#include "Balloon.h"
#include "game.h"

bool Balloon::getExploding() const // explicado en el h
{
	return exploding;
}
Balloon::Balloon(Game* game)
{
	
	//LLamamaos al constructor de mobile object para configurar su velocidad
	//Pasamos un puntero al randomizador del game, es necesario que sea un puntero porque si creamos un randomizador nuevo, tendriamos que meterle
	//lo de los numeros y consumiramos mucho, es necesario que sea un puntero para que sea el randomizador del game
	this->game = game;
	this->Combo = 0;
	this->HitObject = nullptr;
	this->balspeed = game->getbalspeed();
	std::mt19937_64* randomGenerator = (this->game->GetRandomGenerator());
	this->TextureFil = std::uniform_int_distribution<int>(0, 5)(*randomGenerator);
	this->speed = Vector2D<float>(0, std::uniform_real_distribution<float>(-1*this->balspeed, 0.3*this->balspeed)(*randomGenerator));
	int posx = std::uniform_int_distribution<int>(300, 700)(*randomGenerator);
	this->position = Rectangle(Point2D<>(posx, 800), 100, 100);
	this->texture = this->game->getTexture(this->game->BALLOON);

	exploding = false;
	FrameAnimation = 0;
	TimeAnimation = 0.0f;
	TimeFrame = 10.0f;
	this->game->CreateObjects(this);
}

bool Balloon::hit(const Rectangle& rect)
{
	if (!this->exploding)
	{
		Arrow* aux = dynamic_cast<Arrow*>(this->HitObject);
		if (aux != nullptr)
		{
			aux->addCombo(1);
			Combo = aux->getCombo();
		}
		bool b = this->SceneObject::hit(rect);
		this->exploding = b;
	}
	return this->exploding;
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

void Balloon::saveObj(std::ostream& output)
{
	output << "Balloon ";
	MobileObject::saveObj(output);
	//Guardamos el estado del globo
	output <<this->exploding <<" "<<this->Combo << std::endl;
}

Balloon::Balloon(Game* game, std::ifstream &input)
{
	this->game = game;
	//Lectura coordenadas
	float x, y;
	input >> x >> y;
	this->position = Rectangle(Point2D<>(x, y), 100, 100);
	//Lectura textura
	int fil, col;
	input >> fil >> col;
	
	this->TextureFil = fil;
	this->TextureCol = col;
	this->texture = this->game->getTexture(this->game->BALLOON);
	//Lectura velocidad
	input >> x >> y;
	this->speed = Vector2D<float>(x, y);
	//Carga de estado
	int exploding;
	input >> exploding;
	this->exploding = exploding;
	input >> this->Combo;

	FrameAnimation = 0;
	TimeAnimation = 0.0f;
	TimeFrame = 10.0f;
	this->game->CreateObjects(this);
}
