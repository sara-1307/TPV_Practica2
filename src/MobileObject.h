#pragma once
#include "vector2D.h"
#include "SceneObject.h"
class MobileObject : public SceneObject
{
protected: 
	Point2D<> Speed;

public: 
	void SobreUpdate();
};


