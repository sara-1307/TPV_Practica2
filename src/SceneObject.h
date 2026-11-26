#pragma once

#include "texture.h"
#include "rectangle.h"
#include "GameObject.h"
#include "FileFormatError.h"
#include <fstream>
class SceneObject : public GameObject
{
protected:
	Texture* texture; // textura
	Rectangle position; // posicion y ancho alto
	bool death;
	

public:
	virtual bool hit(const Rectangle& obj);
	void explotados();
	SceneObject(Texture* tex, Rectangle rec, Game* game);
	void EscribirDatos(std::ostream& archivo) const override;
	SceneObject(Game* game, std::istream& archivo, Texture* tex, int linea);
	
};



