#pragma once

#include "vector2D.h"
#include "rectangle.h"
#include <SDL3/SDL.h>
#include "texture.h"
#include "Arrow.h"
#include "SceneObject.h"
#include <fstream>


class Game;

class Bow : public SceneObject
{
private:
	Point2D<> Address; // Direcion a la que me muevo
	Point2D<> Speed; // Velocidad a la que me muevo
	int NArrow;
	bool armed;

	float LoadTime;
	float SpeedArrow;

public:
	bool handleEvent(const SDL_Event& event);

	Bow(Rectangle pos, Texture* tex, Point2D<> speed, int NFlechas, bool armado, Point2D<> Address, Game* game);

	void render() const override;
	bool update(float delta) override;

	Point2D<> getposmed();

	float GetArrowSpeed() const;

	void setArrows(int arrows); // Cambio el numero de flechas que tiene el arco

	Arrow* CrearFlecha(); // Para crear la flecha que le pasaremos al game

	void EscribirDatos(std::ostream& archivo) const override;

	Bow(Game* game, std::istream& archivo, Texture* tex, int linea);
};

