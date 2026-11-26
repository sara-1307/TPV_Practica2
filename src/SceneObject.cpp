#include "SceneObject.h"

bool SceneObject::hit(const Rectangle& obj)
{
	if (position.hasIntersection(obj))
	{
		return true;
	}
	return false;
}
void SceneObject::EscribirDatos(std::ostream& archivo) const
{
	archivo << position.getTopLeftCorner().getX() << " " << position.getTopLeftCorner().getY() << " " << position.getWidth() << " "
		<< position.getHeight() << " " << death << " ";
}

SceneObject::SceneObject(Game* game, std::istream& archivo,
	Texture* texture, int linea)
	: GameObject(game), texture(texture)
{
	float x, y, w, h;

	if (!(archivo >> x >> y >> w >> h >> death) || w < 0 || h < 0)
	{
		throw FileFormatError("saved.txt", linea);
	}

	position = Rectangle({ x, y }, w, h);
}
SceneObject::SceneObject(Texture* tex, Rectangle rec, Game* game)
	: GameObject(game), texture(tex), position(rec), death(false)
{
}
