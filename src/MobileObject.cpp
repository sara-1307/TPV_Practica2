#include "MobileObject.h"
#include <ostream>
#include "SceneObject.h"

MobileObject::MobileObject(){}
bool MobileObject::update(float delta)
{
	this->MobileObject::position.move(MobileObject::speed * delta);
	return true;
}
void MobileObject::saveObj(std::ostream& output)
{
	SceneObject::saveObj(output);
	output << this->speed.getX() << " " << this->speed.getY() << " ";
}
