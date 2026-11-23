#pragma once
#include "GameObject.h"
#include <ostream>
#include "texture.h"
#include "rectangle.h"
class SceneObject:public GameObject
{
protected:
	Rectangle position; // posicion y ancho alto
	Texture* texture; // textura
	int TextureFil;
	int TextureCol;
	SceneObject* HitObject;

	SceneObject(Texture* _texture, Rectangle _position);
public:
	SceneObject();
	void render() const override; 
	virtual bool hit(const Rectangle& rect);
	virtual void saveObj(std::ostream& output);
	virtual void hitObj(SceneObject* obj);
	
};

