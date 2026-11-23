#pragma once
#include "MobileObject.h"
#include <ostream>
#include "vector2D.h"


//Declaracion anticipada porque sino hay dependencias circulares
class Game; 
class Arrow : public MobileObject
{
protected:
	int combo;
public: 
	bool update(float delta) override;
	Arrow(Game* game,Point2D<> coordinates,float speed);
	Arrow(Game* game, std::ifstream& input);
	void saveObj(std::ostream& output) override;

	void addCombo(int i);
	int getCombo();
}; 

