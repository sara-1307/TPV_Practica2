#pragma once
#include "vector2D.h"
#include "rectangle.h"
#include "texture.h"


class Balloon
{
private:

	Rectangle Position;
	int color;
	Point2D<>  Speed;
	Texture* texture;
	bool exploit;
	int FrameAnimation; // El  frame en el que estoy
	float TimeAnimation; // el tiempo de la animacion
	float TimeFrame; // el tiempo del frame

	

public:
	Balloon(Rectangle pos, int color, Point2D<> velocidad, Texture* tex);
	bool hit(const Rectangle& obj);
	void render() const;
	bool update(float delta);
	Balloon();
	bool getexploto() const;  // nos permite saber si ese globo ha esplotado es decir el jugador lo revento
};

