#include "SceneObject.h"
#include <ostream>
#include "rectangle.h"


bool SceneObject::hit(const Rectangle& rect)
{
	return position.hasIntersection(rect);
}

void SceneObject::render() const
{
	texture->renderFrame(position.to_sdl(), TextureFil, TextureCol);
}


void SceneObject::EscribirDatos(std::ostream& archivo) const
{
	archivo << position.getTopLeftCorner().getX() << " " << position.getTopLeftCorner().getY() << " " << position.getWidth() << " "
		<< position.getHeight() << " " << death << " ";
	archivo << this->TextureFil << " " << this->TextureCol << " " << this->TextureFil << " " << this->TextureCol << " ";
}
SceneObject::SceneObject(Game* game, std::istream& archivo,	Texture* texture, int linea): GameObject(game), texture(texture)
{
	float x, y, w, h;

	if (!(archivo >> x >> y >> w >> h >> death) || w < 0 || h < 0)
	{
		throw FileFormatError("save", linea);
	}

	position = Rectangle({ x, y }, w, h);
}
SceneObject::SceneObject(Texture* tex, Rectangle rec, Game* game): GameObject(game), texture(tex), position(rec), death(false){}

