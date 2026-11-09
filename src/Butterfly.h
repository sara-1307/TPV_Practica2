#pragma once
#include "MobileObject.h"
#include "Vector2D.h"
class Butterfly : public MobileObject
{
protected: 
	Point2D<> Dirección; 
	bool MeMataron;
	int FrameAnimation; // El  frame en el que estoy
	float TimeAnimation; // el tiempo de la animacion
	float TimeFrame; // el tiempo del frame

public: 
	Butterfly(Point2D<> Dirección, Rectangle pos, Point2D<> velocidad, Texture* textura); 
	void render() const override; 
	bool update(float delta) override; 
};

