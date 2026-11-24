#pragma once
#include "vector2D.h"
#include <fstream>
#include "texture.h"
#include "SceneObject.h"
class MobileObject : public SceneObject
{
protected:
	Vector2D<float> speed; // velocidad 
public:
	MobileObject();
	bool update(float delta) override;
	void saveObj(std::ostream& output) override;

	MobileObject(Point2D<> Speed, Texture* tex, Rectangle rec, Game* game);
	void EscribirDatos(std::ostream& archivo) const override;
	MobileObject(Game* game, std::istream& archivo, Texture* tex, int linea);
};

