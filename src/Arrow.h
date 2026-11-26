#pragma once
#include "vector2D.h"
#include "rectangle.h"
#include "texture.h"
#include "MobileObject.h"

//Declaracion anticipada porque sino hay dependencias circulares
class Game;
class Arrow : public MobileObject
{
private:
	int asesinados; 

public:
	void render() const override;
	bool update(float delta)  override;

	Arrow(Game* game, Texture* tex, Rectangle pos, Point2D<> velocidad);
	Arrow(Game* game, std::istream& archivo, Texture* tex, int linea); // Constructor para leer los archivos
	void EscribirDatos(std::ostream& archivo) const override; // Escribir los datos



};

