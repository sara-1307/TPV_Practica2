#include "SceneObject.h"
#include <ostream>
#include "rectangle.h"

SceneObject::SceneObject() {
	texture = nullptr;
	TextureFil = 0;
	TextureCol = 0;
	SceneObject* HitObject = nullptr;
};
bool SceneObject::hit(const Rectangle& rect)
{
	return position.hasIntersection(rect);
}
void SceneObject::hitObj(SceneObject* obj)
{
	if (this->position.hasIntersection(obj->position))
	{
		this->HitObject = obj;
	}
}

void SceneObject::render() const
{
	texture->renderFrame(position.to_sdl(), TextureFil, TextureCol);
}

void SceneObject::saveObj(std::ostream& output)
{
	//Guardamos coordenadas
	output << this->position.getTopLeftCorner().getX() << " " << this->position.getTopLeftCorner().getY()<<" ";
	//Guardamos fila y columna de textura
	output << this->TextureFil << " " << this->TextureCol << " ";
}
