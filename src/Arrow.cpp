#include "Arrow.h"
#include "game.h"

class Game;
void Arrow::render() const
{
	texture->renderFrame(position.to_sdl(), 0, 0);

}
bool Arrow::update(float delta)
{
	//Declaro las espresiones constante
	constexpr int ArrowWidth = 25;
	constexpr int ArrowHeight = 20;
	constexpr int limit = 800;
	//////////////
	position.move(Speed * delta);
	Point2D<> corner = position.getTopLeftCorner(); 
	float x = corner.getX() + position.getWidth() - ArrowWidth; // quito para que el rectangulo solo este en la derecha donde la punta 
	float y = corner.getY(); //uso todo el ancho
	
	Rectangle ArrowHitbox (Point2D<>(x, y), ArrowWidth, ArrowHeight);
	
	game->checkCollision(ArrowHitbox);
	
	return (position.getTopLeftCorner().getX() < limit); // muere cuando sale de los limites de la pantalla
	
}

Arrow::Arrow(Game* game,Texture* tex, Rectangle pos, Point2D<> velocidad)
{
	this->game = game; 
	this->position = pos; 
	this->Speed = velocidad; 
	this->texture = tex;

}
