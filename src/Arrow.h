#pragma once
#include "vector2D.h"
#include "rectangle.h"
#include "texture.h"
#include "MobileObject.h"

//Declaracion anticipada porque sino hay dependencias circulares
class Game; 
class Arrow :  public MobileObject
{
private:
	

public: 
	void render() const override; 
	bool update(float delta)  override;
	
	Arrow(Game* game,Texture* tex, Rectangle pos,  Point2D<> velocidad);
};

