#include "SceneObject.h"
bool SceneObject::hit(const Rectangle& obj)
{
	if (position.hasIntersection(obj))
	{
		return true;
	}
	return false;
}
