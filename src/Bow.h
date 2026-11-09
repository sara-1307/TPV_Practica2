#pragma once
#include "vector2D.h"
#include "rectangle.h"
#include <SDL3/SDL.h>
#include "texture.h"
#include "arrow.h"
#include "SceneObject.h"
class Bow : public SceneObject
{
private: 

	Point2D<> Address; 
	Point2D<> Speed;
	int NArrow;
	bool armed; 
	
    float LoadTime = 0.0f;  // tiempo para cargar la flecha
	float SpeedArrow = 0.3f; // velocidad predeterminada

	static constexpr float SpeedMin = 0.3f;
	static constexpr float SpeedMax = 2.0f;


	
public:
	bool handleEvent(const SDL_Event& event);
	Bow(Rectangle pos, Texture* tex,  Point2D<> speed, int NFlechas, bool armado, Point2D<> Address);
	void render() const  override;
	bool update(float delta) override;
	Point2D<> getposmed(); //Consigo la posiciond el arco en la mitad para crear la flecha
	float GetArrowSpeed() const;
	void setArrows(int arrows);
	void CrearFlecha();
};

