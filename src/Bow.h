#pragma once
#include "vector2D.h"
#include "rectangle.h"
#include <SDL3/SDL.h>
#include "texture.h"
#include "arrow.h"
class Bow
{
private: 

	Rectangle Position;
	Point2D<>  Address; //Direcion donde nos vamos a mover
	int speedBow;
	int NArrow;
	bool armed; 
	Texture* texture;
    float LoadTime = 0.0f;  // tiempo para cargar la flecha
	float SpeedArrow = 0.3f; // velocidad predeterminada

	static constexpr float SpeedMin = 0.3f;
	static constexpr float SpeedMax = 2.0f;

	
public:
	bool handleEvent(const SDL_Event& event);
	Bow(Rectangle pos, Texture* tex,  Point2D<> velocidad, int NFlechas, bool armado, int speed);
	void render() const;
	bool update(float delta);
	Point2D<> getposmed(); //Consigo la posiciond el arco en la mitad para crear la flecha
	float GetArrowSpeed() const;
	void setArrows(int arrows);
	void CrearFlecha();
};

