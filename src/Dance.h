#pragma once
#include "texture.h"
#include "rectangle.h"
class Dance // esta clase es para el tremendo baile de la muchacha
{   private:
	int frame = 0;
	float TimeAnimation = 0.0f;
	float TimeFrame = 0.1f;
	
	Texture* texture;
	Rectangle position;
    public: 
		Dance(Texture* tex, Rectangle pos);
		Dance(); 
		void render() const;
		bool update(float delta);
		

};

