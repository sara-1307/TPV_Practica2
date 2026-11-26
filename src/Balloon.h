#pragma once
#include "vector2D.h"
#include "rectangle.h"
#include "texture.h"
#include "MobileObject.h"
#include <fstream>
#include "game.h"
class Balloon : public MobileObject
{
private:


	int color;

	int FrameAnimation; // El  frame en el que estoy
	float TimeAnimation; // el tiempo de la animacion
	float TimeFrame; // el tiempo del frame



public:
	Balloon(Rectangle pos, int color, Point2D<> velocidad, Texture* tex, Game* game);
	void render() const override;
	bool hit(const Rectangle& obj)  override;
	bool update(float delta) override;
	Balloon();
	bool getexploto() const;  // nos permite saber si ese globo ha explotado es decir el jugador lo revento
	void EscribirDatos(std::ostream& archivo) const override; // Escribe los datos del globo
	Balloon(Game* game, std::istream& archivo, Texture* tex, int linea);
};

