#pragma once
#include "Vidas.h"
#include "Puntuacion.h"
#include "GameObject.h"

#include <vector>
#include <string>
using namespace std;
class InfoBar : public GameObject
{
private:
	std::vector<Vidas> Lifes;
	std::vector<Puntuacion> Point;
	
public:
	InfoBar(Texture* texpunt, Texture* texvidas, Texture* texdance, int Arrows, string objetive, Game* game);
	void render() const override;
	void updatelife(); // Actualizamos las vidad del jugador
	void updatepoint(int point);  // actualizamos los puntos
	void showanimation(float delta);  // mostrarmos animacion
	void update(int arrows, Texture* texvidas, float delta, int point); // Actualizar
	bool  update(float delta) override;
	void PuntosProsimoNivel(string objetive, Texture* texpunt); // Para cuando leeamos un nuevo nivel

	void EscribirDatos(std::ostream& archivo) const override;


};

