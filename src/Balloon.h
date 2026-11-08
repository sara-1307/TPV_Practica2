#pragma once
#include "vector2D.h"
#include "rectangle.h"
#include "texture.h"
#include "MobileObject.h"

class Balloon : public MobileObject
{
private:


	int color;
	bool exploit;
	int FrameAnimation; // El  frame en el que estoy
	float TimeAnimation; // el tiempo de la animacion
	float TimeFrame; // el tiempo del frame

	

public:
	Balloon(Rectangle pos, int color, Point2D<> velocidad, Texture* tex);
	bool hit(const Rectangle& obj);
	void render() const override;
	bool update(float delta) override;
	Balloon();
	bool getexploto() const;  // nos permite saber si ese globo ha esplotado es decir el jugador lo revento
};

