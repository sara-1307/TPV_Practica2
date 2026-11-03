#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <array>
#include <istream>
#include <vector>
#include <fstream>
#include <string>
#include "rectangle.h"
#include "Balloon.h"
#include "Arrow.h"
#include "Bow.h"
#include <vector>
#include <random>
#include "InfoBar.h"
using namespace std;

// Declaraciones anticipadas
class Texture;
// uno
/**
 * Clase principal del juego.
 */
class Game
{
public:
	// Número de actualizaciones por segundo
	static constexpr int FRAME_RATE = 30;
	// Periodo entre actualizaciones en milisegundos
	static constexpr int FRAME_PERIOD = 1000 / FRAME_RATE;
	// Tamaño real de la ventana
	static constexpr int WINDOW_WIDTH = 800; // ancho
	static constexpr int WINDOW_HEIGHT = 600; // altura

	enum TextureName
	{
		BOW = 0,
		ARROW,
		BALLOON,
		DANCE,
		DIGITS,
		NUM_TEXTURES
	};

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::array<Texture*, NUM_TEXTURES> textures;

	void render() const;
	void update();
	void handleEvents();

	bool exit;
	float StartTime = 0; 
	float FrameTime = 0;
	bool ganaste = false;
	Bow* bow;
	std::vector<Arrow*> arrow;
	std::vector<Balloon*> balloon;
	float baldelay;
	int cont;
	int arrows;
	std::mt19937_64 randomGenerator;
	double deltatime;
	int puntuacion;
	int goal;
    int ballpoints;
	InfoBar* infoBar;
	float TimeBalloons;
	 int level = 1;
	 int Red = 0;
	 int Green = 0;
	 int Blue = 0;


public:
	Game();
	~Game();

	// Obtiene una textura por su nombre
	Texture* getTexture(TextureName name) const;
	void Eliglob(std::vector<Balloon*>&bal, int i); // elimina los globos
	void Eliarrow(std::vector<Arrow*>& arrow, int i); // elimina las flechas
	// Ejecuta el bucle principal del juego
	void run();
	bool loadLevel(string archivo);

	// Comprueba si hay algún objeto colocado en ese rectángulo
	bool checkCollision(const Rectangle& rect);

	void CreateBalloon();
};

inline Texture*
Game::getTexture(TextureName name) const
{
	return textures[name];
}

#endif // GAME_H
