#pragma once
#include "Vidas.h"
#include "Puntuacion.h"
#include "Dance.h"
#include <vector>
#include <string>
using namespace std;
class InfoBar
{
private:
	std::vector<Vidas> Lifes;
	std::vector<Puntuacion> Point;
	Dance dance;
public:
	InfoBar( Texture* texpunt, Texture* texvidas, Texture* texdance, int Arrows, string objetive);
	void render() const;
	void updatelife(); // Actualizamos las vidad del jugador
    void updatepoint(int point);  // actualizamos los puntos
	void showanimation(float delta);  // mostrarmos animacion
	void update(int arrows, Texture* texvidas, float delta); // Actualizar
	void PuntosProsimoNivel(string objetive, Texture* texpunt); // Para cuando leeamos un nuevo nivel
	 

	
};

