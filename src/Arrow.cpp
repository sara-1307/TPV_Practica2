#include "Arrow.h"
#include "game.h"

class Game;
bool Arrow::update(float delta)
{
	//Declaro las espresiones constante
	constexpr int ArrowWidth = 25;
	constexpr int ArrowHeight = 20;
	constexpr int limit = 800;

	MobileObject::update(delta);
	Point2D<> corner = position.getTopLeftCorner(); 
	float x = corner.getX() + position.getWidth() - ArrowWidth; // quito para que el rectangulo solo este en la derecha donde la punta 
	float y = corner.getY(); //uso todo el ancho
	
	Rectangle ArrowHitbox (Point2D<>(x, y), ArrowWidth, ArrowHeight);
	
	game->checkCollision(ArrowHitbox);
	
	return (position.getTopLeftCorner().getX() < limit); // muere cuando sale de los limites de la pantalla
}
void Arrow::EscribirDatos(std::ostream& archivo) const
{
	archivo << "Arrow ";
	MobileObject::EscribirDatos(archivo);
	archivo << "\n";
}
Arrow::Arrow(Game* game, std::istream& archivo, Texture* tex, int linea) :MobileObject(game, archivo, tex, linea)
{

}
Arrow::Arrow(Game* game, Texture* tex, Rectangle pos, Point2D<> velocidad) : MobileObject(velocidad, tex, pos, game)
{


}
//void Arrow::saveObj(std::ostream& output)
//{
//	output << "Arrow ";
//	MobileObject::saveObj(output);
//}
//Arrow::Arrow(Game* game,Point2D<> coordinates,float speed)
//{
//	this->game = game;
//	this->position = Rectangle(coordinates, 100, 20);
//	this->texture = this->game->getTexture(game->ARROW);
//	this->speed = Vector2D<float>(speed,0);
//	this->game->CreateObjects(this);
//	this->combo = 0;
//	
//}
//Arrow::Arrow(Game* game, std::ifstream& input)
//{
//	this->game = game;
//	//Lectura coordenadas
//	int x, y;
//	input >> x >> y;
//	this->position = Rectangle(Point2D<>(x, y), 100, 20);
//	//Lectura textura
//	int fil, col;
//	input >> fil >> col;
//	this->TextureFil = fil;
//	this->TextureCol = col;
//	this->texture = this->game->getTexture(this->game->ARROW);
//	//Lectura velocidad
//	input >> x >> y;
//	this->speed = Vector2D<float>(x, y);
//	input >> combo;
//	this->game->CreateObjects(this);
//
//}


void Arrow::addCombo(int i)
{
	this->combo += i;
}
int Arrow::getCombo()
{
	return this->combo;
}
