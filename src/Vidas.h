#pragma once
#include "rectangle.h"
#include "texture.h"
class Vidas
{
private:
	Texture* textura;
	Rectangle pos;
public:
	Vidas(Texture* tex, Rectangle pos);
	void render() const;
	
};

