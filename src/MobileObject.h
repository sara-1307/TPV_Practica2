#pragma once
#include "vector2D.h"
#include "SceneObject.h"
#include "texture.h"
#include <fstream>
class MobileObject : public SceneObject
{
protected:
	Point2D<> Speed;

public:
	void SobreUpdate();

	MobileObject(Point2D<> Speed, Texture* tex, Rectangle rec, Game* game);
	void EscribirDatos(std::ostream& archivo) const override;
	MobileObject(Game* game, std::istream& archivo, Texture* tex, int linea);
};


