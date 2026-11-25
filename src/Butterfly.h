#pragma once
#include "MobileObject.h"
#include "vector2D.h"

class Game;
class Butterfly : public MobileObject
{
protected:
	Point2D<> Dirección;
	float mismadir; // Contador para ir viendo a que dirección voy
	float limitdir;  // El limite de tiempo en los que puedo ir a una misma dirección

	int FrameAnimation; // El  frame en el que estoy
	float TimeAnimation; // el tiempo de la animacion
	float TimeFrame; // el tiempo del frame


public:
	Butterfly(Point2D<> Dirección, Rectangle pos, Point2D<> velocidad, Texture* textura, float limitdir, Game* game);

	void render() const override;
	bool update(float delta) override;

	bool hit(const Rectangle& obj) override;

	void EscribirDatos(std::ostream& archivo) const override;
	Butterfly(Game* game, std::istream& archivo, Texture* tex, int linea);
};

