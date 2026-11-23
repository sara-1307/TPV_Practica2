#include "Butterfly.h"
#include "rectangle.h"

Butterfly::Butterfly(Game* game)
{
	this->game = game;
	this->maxSpeed = 0.3;
	this->randomGenerator = game->GetRandomGenerator();
	this->speed = Vector2D<float>(std::uniform_real_distribution<float>(-maxSpeed,maxSpeed)(*randomGenerator), std::uniform_real_distribution<float>(-maxSpeed, maxSpeed)(*randomGenerator));
	this->texture = game->getTexture(this->game->BUTTERFLY);
	int posx = std::uniform_int_distribution<int>(0, this->game->WINDOW_WIDTH)(*randomGenerator);
	int posy = std::uniform_int_distribution<int>(0, this->game->WINDOW_HEIGHT)(*randomGenerator);
	this->position = Rectangle(Point2D<>(posx, posy), 45, 45);
	this->dirChangeTimer = 0;
	this->dirChangeLimit = std::uniform_real_distribution<float>(0, 500)(*randomGenerator);
	this->dead = false;
	this->game->CreateObjects(this);

}
Butterfly::Butterfly(Game* game, std::ifstream& input)
{
	this->game = game;
	//Lectura coordenadas
	float x, y;
	input >> x >> y;
	this->position = Rectangle(Point2D<>(x, y), 45, 45);
	//Lectura textura
	int fil, col;
	input >> fil >> col;
	this->TextureFil = fil;
	this->TextureCol = col;
	this->texture = this->game->getTexture(this->game->BUTTERFLY);
	//Lectura velocidad
	input >> x >> y;
	this->speed = Vector2D<float>(x, y);
	//Cargamos estado
	input >> this->dead;

	this->maxSpeed = 0.3;
	this->randomGenerator = game->GetRandomGenerator();
	this->dirChangeTimer = 0;
	this->dirChangeLimit = std::uniform_real_distribution<float>(0, 500)(*randomGenerator);
	this->game->CreateObjects(this);
}
bool Butterfly::update(float delta)
{
	if (!dead)
	{
		if (dirChangeTimer > dirChangeLimit)
		{
			dirChangeTimer = 0;
			dirChangeLimit = std::uniform_real_distribution<float>(0, 500)(*randomGenerator);
			this->speed = Vector2D<float>(std::uniform_real_distribution<float>(-maxSpeed, maxSpeed)(*randomGenerator), std::uniform_real_distribution<float>(-maxSpeed, maxSpeed)(*randomGenerator));
		}
		dirChangeTimer += delta;
		int x = this->position.getTopLeftCorner().getX();
		int y = this->position.getTopLeftCorner().getY();
		if (y > this->game->WINDOW_HEIGHT || y <= 0 || x > this->game->WINDOW_WIDTH || x <= 0)
		{
			this->speed = Vector2D<float>(-this->speed.getX(), -this->speed.getY());
		}
		setAnimDir();
	}
	else
	{
		this->speed = Vector2D<float>(0, 1);
		if (this->position.getTopLeftCorner().getY() > this->game->WINDOW_HEIGHT)
		{
			this->game->addPoints(-this->game->getBalPoints());
			return false;
		}
	}
	MobileObject::update(delta);
	return true;
}
void Butterfly::setAnimDir()
{
	if (this->TextureCol < 10)
	{
		this->TextureCol++;
	}
	else
	{
		this->TextureCol = 0;
	}
	if (this->speed.getX() > 0)
	{
		this->TextureFil = 1;
	}
	else if (this->speed.getX() < 0)
	{
		this->TextureFil = 0;
	}
	else
	{
		this->TextureFil = 2;
	}
}
void Butterfly::render() const 
{ 
	SceneObject::render();
}
bool Butterfly::hit(const Rectangle& rect)
{
	if (!this->dead)
	{

		bool b = this->SceneObject::hit(rect);
		if (b)
		{
			this->game->setNButterflies((this->game->getNbutterflies()) - 1);
		}
		this->dead = b;
		
	}
	return this->dead;
}
void Butterfly::saveObj(std::ostream& output)
{
	output << "Butterfly ";
	MobileObject::saveObj(output);
	output << this->dead<<endl;
}
