#pragma once
#include "vector2D.h"
#include "rectangle.h"
#include "texture.h"

//Declaracion anticipada porque sino hay dependencias circulares
class Game; 
class Arrow
{
private:
	Game* game; // puntero a game
	Rectangle position; // posicion y ancho alto
	Point2D<>  speed; // velocidad 
	Texture* texture; // textura

public: 
	void render() const; 
	bool update(float delta);
	
	Arrow(Game* game,Texture* tex, Rectangle pos,  Point2D<> velocidad);
};

