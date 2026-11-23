#pragma once
#include "MobileObject.h"
#include <ostream>
#include "Bow.h"

class Bow : public MobileObject
{
private:
//variable para almacenar la velocidad del arco (usaremos esto para cambiar la speed de MobileObject
	int BowSpeed;
	//Número de flechas
	int NArrow;
	//Arco cargado o no
	bool armed;
	//Cargando o no la flecha;
	bool charging;
    float LoadTime = 0.0f;  // tiempo para cargar la flecha
	float SpeedArrow = 0.3f; // velocidad predeterminada

	static constexpr float SpeedMin = 0.1f;
	static constexpr float SpeedMax = 5.0f;

	
public:
	bool handleEvent(const SDL_Event& event);
	Bow(Game*game,int velocidad, int NFlechas);
	//void render() const;
	bool update(float delta);
	Point2D<> getMediumPos(); //Consigo la posiciond el arco en la mitad para crear la flecha
	float GetArrowSpeed() const;
	void setArrows(int arrows);
	int getArrows();
	void saveObj(std::ostream& output) override;
	Bow(Game* game, std::ifstream& input);
};

