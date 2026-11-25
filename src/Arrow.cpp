#include "Arrow.h"
#include "game.h"

class Game;

void Arrow::addCombo(int i)
{
	this->combo += i;
}
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
	
	if(game->checkCollision(ArrowHitbox))
	{
		addCombo(1);
	}
	
	if (position.getTopLeftCorner().getX() > limit)
	{
		game->DarPuntuacion(combo); // Una vez la flecha ya ha salido significa que no puede dar a mas globos por lo que ya se pueden sumar los puntos conseguido con esa flecha
		return false;
	}
	else
	{
		return true;
	}
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




int Arrow::getCombo()
{
	return this->combo;
}
