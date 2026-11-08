#pragma once

#include "texture.h"
#include "rectangle.h"
#include "GameObject.h"
class SceneObject : public GameObject
{
protected: 
	Texture* texture; // textura
	Rectangle position; // posicion y ancho alto

public: 
	bool hit(const Rectangle& obj);
};

