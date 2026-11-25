#pragma once
#include "GameObject.h"
#include <ostream>
#include "texture.h"
#include "rectangle.h"
#include "FileFormatError.h"
#include <fstream>
class SceneObject:public GameObject
{
protected:
	Rectangle position; // posicion y ancho alto
	Texture* texture; // textura
	int TextureFil;
	int TextureCol;
	bool death;

	//SceneObject(Texture* _texture, Rectangle _position);
public:
	SceneObject();
	void render() const override; 
	virtual bool hit(const Rectangle& rect);
	SceneObject(Texture* tex, Rectangle rec, Game* game);
	void EscribirDatos(std::ostream& archivo) const override;
	SceneObject(Game* game, std::istream& archivo, Texture* tex, int linea);
	
};

