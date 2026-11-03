#pragma once
#include "rectangle.h"
#include "texture.h"
class Puntuacion
{

private:
	Texture* texture;
	Rectangle position;
	int frame;
public:
	Puntuacion(Texture* tex, Rectangle pos);
	void update(int pos);
	void render() const;
	void Change(int pos);
};

