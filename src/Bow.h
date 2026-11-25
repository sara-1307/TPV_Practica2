#pragma once
#include "MobileObject.h"
#include <ostream>
#include "Bow.h"
#include "SceneObject.h"

class Bow : public SceneObject
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

	Point2D<> Address; // Direcion a la que me muevo
	Point2D<> speed; // Velocidad a la que me muevo

	static constexpr float SpeedMin = 0.1f;
	static constexpr float SpeedMax = 5.0f;

	
public:
	bool handleEvent(const SDL_Event& event);
	
	void render() const;
	bool update(float delta) override;
	Point2D<> getMediumPos(); //Consigo la posiciond el arco en la mitad para crear la flecha
	float GetArrowSpeed() const;
	void setArrows(int arrows);
	int getArrows();

	Bow(Rectangle pos, Texture* tex, Point2D<> speed, int NFlechas, bool armado, Point2D<> Address, Game* game);
	void EscribirDatos(std::ostream& archivo) const override;
	Bow(Game* game, std::istream& archivo, Texture* tex, int linea);


	
};

