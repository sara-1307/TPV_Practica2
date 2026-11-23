#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <array>
#include <list>
#include <istream>
#include <fstream>
#include <string>
#include "rectangle.h"
#include "Balloon.h"
#include "Arrow.h"
#include "Bow.h"
#include <random>
#include "InfoBar.h"
#include "GameObject.h"
using namespace std;

// Declaraciones anticipadas
class InfoBar;
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
		DIGITS,
		BUTTERFLY,
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
	bool thereAreButterflies;
	//Objetos de juego
	Bow* bow;
	std::list<SceneObject*> SceneObjectsList;
	
	//Variables que controlan el spawn de globo
	float baldelay;
	int cont;
	int nButterflies = 0;
	int balspeed = 1;
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

	std::mt19937_64* GetRandomGenerator();
	// Obtiene una textura por su nombre
	Texture* getTexture(TextureName name) const;
	// Ejecuta el bucle principal del juego
	void run();
	bool loadLevel(string archivo);

	// Comprueba si hay algún objeto colocado en ese rectángulo
	bool checkCollision(const Rectangle& rect,SceneObject* obj);

	void CreateObjects(SceneObject* obj);
	void addPoints(int p);
	int getBalPoints()const;
	int getPoints()const;
	int getGoal()const;
	int getArrows()const;
	int getbalspeed()const;

	int getNbutterflies()const;
	void setNButterflies(int i);

	

	void saveFile(string file);
	void loadFile(string file);

	void CheckGoal();
	
};




inline Texture*
Game::getTexture(TextureName name) const
{
	return textures[name];
}

#endif // GAME_H
