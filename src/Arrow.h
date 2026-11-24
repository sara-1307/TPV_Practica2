#pragma once
#include "MobileObject.h"
#include <ostream>
#include "vector2D.h"


//Declaracion anticipada porque sino hay dependencias circulares
class Game; 
class Arrow : public MobileObject
{
protected:
	int combo;
public: 
	bool update(float delta) override;
	/*Arrow(Game* game,Point2D<> coordinates,float speed);
	Arrow(Game* game, std::ifstream& input);
	void saveObj(std::ostream& output) override;*/

	void addCombo(int i);
	int getCombo();

	Arrow(Game* game, Texture* tex, Rectangle pos, Point2D<> velocidad);
	Arrow(Game* game, std::istream& archivo, Texture* tex, int linea); // Constructor para leer los archivos
	void EscribirDatos(std::ostream& archivo) const override; // Escribir los datos
}; 

