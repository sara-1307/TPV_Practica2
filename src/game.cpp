#include "game.h"
#include "game.h"

#include <string>

#include <SDL3_image/SDL_image.h>

#include "texture.h"
#include "Balloon.h"
#include "Bow.h"
#include <random>
#include "Butterfly.h"

//INCLUSION DE EXCEPCIONES
#include "SDLError.h"
#include "FileFormatError.h"
#include "FileNotFound.h"
#include "GameError.h"


using namespace std;
// uno
// Constantes
constexpr const char* const WINDOW_TITLE = "Bow & Arrow 1.0";

constexpr const char* IMAGE_ROOT = "../assets/images/";
constexpr const char* LEVEL_ROOT = "../assets/levels/";

// Estructura para especificar las texturas que hay que
// cargar y el tamaño de su matriz de frames
struct TextureSpec
{
	const char* name;
	int nrows = 1;
	int ncols = 1;
};
constexpr array<TextureSpec, Game::NUM_TEXTURES> textureList{
	TextureSpec{"bow.png", 1, 2},
	{"arrow.png"},{"balloons.png",7,6},{"digits.png",1,10},{"butterfly.png",4,10}
};


Game::Game()
  : exit(false),
	randomGenerator(std::random_device{}())
{
	// Carga SDL y crea la ventana con su renderizador
	if (!SDL_Init(SDL_INIT_VIDEO))
		throw SDLError();

	if (!SDL_CreateWindowAndRenderer(WINDOW_TITLE,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		0, &window, &renderer))
		throw SDLError();

	// Carga las texturas al inicio
	//Indice que usaremos para ver que textura nos falla cuando hacemos el catch
	size_t ExceptionIndex = 0;
	try {
		textures.fill(nullptr);
		string imgRoot = IMAGE_ROOT;

		for (size_t i = 0; i < textures.size(); i++) {
			ExceptionIndex++;
			auto [name, nrows, ncols] = textureList[i];
			textures[i] = new Texture(renderer, (imgRoot + name).c_str(), nrows, ncols);
		}
		
	}
	catch (const string& error) {
		
		for (int i = 0; i < textures.size();i++)
		{
			delete textures[i];
		}
		auto [name, nrows, ncols] = textureList[ExceptionIndex];
		throw FileNotFound(name); // relanza la excepción
	}

	// Configura que se pueden utilizar capas translúcidas
	// SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	if(!(loadLevel((to_string(level) + ".txt"))))
	{
		for (int i = 0; i < textures.size();i++)
		{
			delete textures[i];

		}
		throw FileNotFound((to_string(level) + ".txt"));
	}
	
	

	for (int i = 0; i < nButterflies; i++)
	{
		new Butterfly(this);
	}
	infoBar = new InfoBar(this);
	cont = deltatime =  puntuacion = TimeBalloons = 0; // Se que deltatime no lo uso es porque quiero preguntarle algo a Rubén y lo dejo para cuando lo pregunte
	
	
}
Game::~Game()
{
	delete infoBar;
	infoBar = nullptr;
	SceneObject* aux;
	bow = nullptr;
	for (auto i = SceneObjectsList.begin(); i != SceneObjectsList.end(); i++)
	{
		aux = *i;
		delete aux;
	}
	SceneObjectsList.clear();
	

		for (int i = 0; i < textures.size();i++)
		{
			delete textures[i];
			
		}
}
std::mt19937_64* Game::GetRandomGenerator()
{
	return &randomGenerator;
}
void Game::render() const
{
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, Red, Green, Blue, 255);
	
	for (auto i = SceneObjectsList.begin(); i != SceneObjectsList.end();i++) 
	{
		(*i)->render();
	}
	infoBar->render();
	SDL_RenderPresent(renderer);
}
void Game::CreateObjects(SceneObject* obj)
{
	SceneObjectsList.push_back(obj);
}
void Game::update()
{
	//Calculamos el principio del frame (Deltatime)
	StartTime = SDL_GetTicks();
	//Calculamos el temporizador para spawnear los nuevos globos
	TimeBalloons += FRAME_PERIOD; 
	if (TimeBalloons >=baldelay)
	{
		new Balloon(this);
		TimeBalloons = 0;
	}
	//Updateamos todos los objetos del juego
	auto i = SceneObjectsList.begin();
	auto auxIt = SceneObjectsList.begin();
	bool erase = false;
	SceneObject* aux = nullptr;
	while(i != SceneObjectsList.end() && !erase)
	{
		erase = !(*i)->update(FRAME_PERIOD);
		aux = *i;
		auxIt = i;
		i++;
		
	}	
	if (erase)
	{
		SceneObjectsList.erase(auxIt);
		delete aux;
	}
	//UPDATEAMOS INFOBAR
	infoBar->update(FRAME_PERIOD);
	if (bow->getArrows() <= 0)
	{
		exit = true;
	}
	if (nButterflies == 0 && thereAreButterflies)
	{
		exit = true;
	}
	//Calculamos el tiempo entre los frames y frenamos el programa ese tiempo para mantener los frames correctamente
	FrameTime = SDL_GetTicks() - StartTime;
	if (FrameTime < FRAME_PERIOD)
	{
		SDL_Delay(FRAME_PERIOD - FrameTime);
	}

}
void Game::CheckGoal()
{
	if (puntuacion >= goal)
	{
		level++;
		if (!(loadLevel((to_string(level) + ".txt"))))
		{
			ganaste = true;
			exit = true;
		}
		else
		{
			puntuacion = 0;
			TimeBalloons = 0;
			bow->setArrows(arrows);
		}
	}
}
void Game::run()
{
	while (!exit) {	
	
		handleEvents();
		update();
		render();
	}
}
void Game::handleEvents()
{
	SDL_Event event;
	
	// Only quit is handled directly, everything else is delegated
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT)
		{
			exit = true;
		}
		else
		{//Usamos el & en el KMOD ya que es el operador "and bit a bit", si usaramos el == compararía TODOS los bits del mod, y no daría correcto
			if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_S && event.key.mod & SDL_KMOD_CTRL)//&& event.key.mod == SDL_KMOD_CTRL)
			{
				saveFile("datos.txt");
			}
			if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_O && event.key.mod & SDL_KMOD_CTRL)//&& event.key.mod == SDL_KMOD_CTRL)
			{
				loadFile("datos.txt");
			}
			bow->handleEvent(event); // Devuelve true cuando tiene que crear una flecha
			
			
			
		}
	}
}
bool Game::checkCollision(const Rectangle& rect,SceneObject* obj)
{
	bool aux = false;
	auto i = SceneObjectsList.begin();
	while (i != SceneObjectsList.end()  && !aux) //Recorro hasta encontrar un globo con el que choque
	{
		(*i)->hitObj(obj);
		aux = ((*i)->hit(rect));
		
		i++;
	}
	
	return i != SceneObjectsList.end();
	
 }
bool Game::loadLevel(string archivo)
{
	//Borramos los objetos de la esccena para limpiar el nivel
	SceneObject* aux;
	bow = nullptr;
	for (auto i = SceneObjectsList.begin(); i != SceneObjectsList.end(); i++)
	{
		aux = *i;
		delete aux;
	}
	SceneObjectsList.clear();
	
	//Asumimos que no van a haber mariposas, luego si encontramos una la ponemos a true
	this->thereAreButterflies = false;
		
	//Creamos el nuevo arco

	ifstream archi(string(LEVEL_ROOT) +  archivo);
	if (!archi)
	{
		return false;
	}
	string palabras; 
	int line = 0;
	while (archi >> palabras)
	{
		line++;
		if (palabras[0] == '#') { archi.ignore(1000, '\n'); line++; }
		else if (palabras == "arrows")
		{
			archi >> arrows;
		}
		else if (palabras == "butterflies")
		{
			archi >> nButterflies;
			thereAreButterflies = nButterflies > 0;
		}
		else if (palabras == "baldelay")
		{
			archi >> baldelay;
		}
		else if (palabras == "goal")
		{
			archi >> goal;
		}
		else if (palabras == "balpoints")
		{
			archi >> ballpoints;
		}
		else if (palabras == "balspeed")
		{
			archi >> balspeed;
		}
		else if (palabras == "bgcolor")
		{
			archi >> Red >> Green >> Blue;
		}
		else
		{
			archi.close();
			throw FileFormatError(archivo, line);
		}

		if (archi.fail())
		{
			archi.close();
			throw FileFormatError(archivo, line);
		}
	}
	archi.close();
	bow = new Bow(this, 1, arrows);
	return true;
}
int Game::getPoints()const
{
	return puntuacion;
}
int Game::getGoal()const
{
	return goal;
}
void Game::addPoints(int p)
{
	this->puntuacion += p;
	if (puntuacion < 0)
	{
		puntuacion = 0;
	}
}
int Game::getBalPoints()const{
	return ballpoints;
}
int Game::getArrows()const
{
	return bow->getArrows();
}
int Game::getbalspeed()const
{
	return balspeed;
}
void Game::saveFile(string file)
{
	ofstream output(LEVEL_ROOT+file);

	if (!output)
	{
		throw FileNotFound(file);
	}

	output << "Game " << level<< " "<<puntuacion <<" "<<thereAreButterflies << endl;

	for (auto i = SceneObjectsList.begin(); i != SceneObjectsList.end(); i++)
	{
		(*i)->saveObj(output);
	}
	
}
void Game::loadFile(string file)
{

	//Intentamos cargar el archivo
	ifstream LoadFile(LEVEL_ROOT + file);

	if (!LoadFile)
	{
		throw FileNotFound(file);
		return;
	}

	//Borramos los objetos actuales
	bow = nullptr;
	SceneObject* aux;
	for (auto i = SceneObjectsList.begin(); i != SceneObjectsList.end(); i++)
	{
		aux = *i;
		delete aux;
	}
	SceneObjectsList.clear();
	
	//Vamos cargando los objetos que leemos
	string word;
	int line = 0;
		while (LoadFile>> word)
		{	
			try
			{
				if (word == "Game")
				{
					line++;
					int lvl;
					LoadFile >> lvl;
					loadLevel(to_string(lvl) + ".txt");
					LoadFile >> puntuacion;
					LoadFile >> this->thereAreButterflies;
				}
				else if (word == "Arrow")
				{
					line++;
					new Arrow(this, LoadFile);
				}
				else if (word == "Balloon")
				{
					line++;
					new Balloon(this, LoadFile);
				}
				else if (word == "Bow")
				{
					line++;
					bow = new Bow(this, LoadFile);
				}
				else if (word == "Butterfly")
				{
					line++;
					new Butterfly(this, LoadFile);
				}
				else
				{
					line++;
					throw FileFormatError(string(LEVEL_ROOT + file),line);
				}
			}
			catch(GameError e)
			{
				LoadFile.close();
				throw FileFormatError(string(LEVEL_ROOT + file), line);
			}
				
		}
		LoadFile.close();
		SDL_Delay(1000);

}

int Game::getNbutterflies()const
{
	return this->nButterflies;
}
void Game::setNButterflies(int i)
{
	this->nButterflies = i;
}

