#pragma once
#include "vector2D.h"
#include <ostream>
#include "SceneObject.h"
class MobileObject : public SceneObject
{
protected:
	Vector2D<float> speed; // velocidad 
public:
	MobileObject();
	bool update(float delta) override;
	void saveObj(std::ostream& output) override;
};

