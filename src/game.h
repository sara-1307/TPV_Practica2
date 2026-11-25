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

#include <vector>
#include <random>
#include "InfoBar.h"
#include "GameObject.h"
#include "SceneObject.h"
#include <algorithm>
#include <list>
#include "Butterfly.h"
#include "FileNotFound.h"

using namespace std;

// Declaraciones anticipadas
class Texture;
// uno
/**
 * Clase principal del juego.
 */
class Bow;
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
	bool ganaste = false; // Controla si ganaste o perdiste
	Bow* bow;
	list<GameObject*> gameobjetc;
	list<SceneObject*> sceneobject;
	int NMariposa;

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
	void CreateBalloon(); // Crea los globos

public:
	Game();
	~Game();
	void EscribirDatos(std::ostream& archivo);
	// Obtiene una textura por su nombre
	Texture* getTexture(TextureName name) const;
	void Quitarpuntuación(int point);
	void DarPuntuacion(int mul);
	// Ejecuta el bucle principal del juego
	void run();
	bool loadLevel(string archivo);
	void RevisarMeta();
	// Comprueba si hay algún objeto colocado en ese rectángulo
	bool checkCollision(const Rectangle& rect);


	void addObject(SceneObject* obj);  // añade los objetos a la lista
	void save();
	void cargar();
	int nuevadir();  // Responsable de dar nuevas direciones a la amriposas
	void GenerarMariposas();
	int getArrows() const;
	int getGoal() const;
	int getPoint() const;
	int getBallPoint() const;
	int getPoints() const;
};

inline Texture*
Game::getTexture(TextureName name) const
{
	return textures[name];
}


#endif // GAME_H
