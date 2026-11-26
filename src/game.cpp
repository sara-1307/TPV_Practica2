#include "game.h"

#include <string>

#include <SDL3_image/SDL_image.h>

#include "texture.h"
#include <vector>
#include "Balloon.h"
#include "SDLError.h"
#include "GameError.h"
#include "Bow.h"
#include <sstream>





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
	{"arrow.png"},{"balloons.png",7,6},{"Dance.png", 1,6},{"digits.png",1,10},{"butterfly.png", 4,10 },
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
	try {
		textures.fill(nullptr);
		string imgRoot = IMAGE_ROOT;

		for (size_t i = 0; i < textures.size(); i++) {
			auto [name, nrows, ncols] = textureList[i];
			textures[i] = new Texture(renderer, (imgRoot + name).c_str(), nrows, ncols);
		}
	}
	catch (const GameError& error) {
		std::cout << error.what() << endl;
		for (int i = 0; i < textures.size();i++)
		{
			delete textures[i];

		}
		throw error; // relanza la excepción
	}

	// Configura que se pueden utilizar capas translúcidas
	// SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	try
	{
		if (!loadLevel(to_string(level) + ".txt"))
		{
			throw FileNotFound(to_string(level) + ".txt");
		}
	}
	catch (const GameError&)
	{
		for (int i = 0; i < textures.size(); i++)
		{
			delete textures[i];
			textures[i] = nullptr;
		}

		throw;
	}



	Rectangle rectArco(Point2D<>(100, 100), 100, 100);
	bow = new Bow(rectArco, getTexture(BOW), Point2D<>(0, 1), arrows, true, Point2D<>(0, 0), this);
	cont = deltatime = puntuacion = TimeBalloons = 0; // Se que deltatime no lo uso es porque quiero preguntarle algo a Rubén y lo dejo para cuando lo pregunte
	infoBar = new InfoBar(this);
	gameobjetc.push_back(infoBar);

	GenerarMariposas();



}
void Game::GenerarMariposas()
{
	;
	for (int i = 0; i < NMariposa; i++)
	{
		int posx = std::uniform_int_distribution<int>(100, 500)(randomGenerator);
		int posy = std::uniform_int_distribution<int>(100, 500)(randomGenerator);
		float cambiotiempo = std::uniform_int_distribution<int>(3000, 10000)(randomGenerator);
		float velocidad = std::uniform_real_distribution<float>(0.01f, 0.2f)(randomGenerator);
		Rectangle rectball(Point2D<>(posx, posy), 50, 50);
		Butterfly* but = new Butterfly(Point2D<>(0, 0), rectball, Point2D<>(velocidad, velocidad), getTexture(BUTTERFLY), cambiotiempo, this);
		sceneobject.push_back(but);

	}
}
void Game::addObject(SceneObject* obj)
{
	sceneobject.push_back(obj);
}
void Game::EscribirDatos(std::ostream& archivo)
{
	archivo << "Game " << level << " " << puntuacion << " " << arrows << " " << ganaste << "\n";
}
void Game::save()
{
	ofstream out("saved.txt");
	EscribirDatos(out);
	bow->EscribirDatos(out);
	for (list<SceneObject*>::iterator it = sceneobject.begin(); it != sceneobject.end(); ++it)
	{
		(*it)->EscribirDatos(out);
	}

}
void Game::cargar() // Nota para mi Importante como esto son constructoras lo que estoy usando se llama primero al del padre y leugo al hijo, esto hace que cuando se lea el archivo el padre sea el primero en leer por lo que los atributos se tienen que guardar en el mismo orden de lectura es decir atributos del padre y leugo del hijo, lo pongo porque me implosiono en proyecto 100000 veces por esto y es bueno tenerlo en cosideración en futuro 
{
	ifstream archivo("saved.txt");

	if (!archivo.is_open())
	{
		throw FileNotFound("saved.txt");
	}
	string tipo;
	int nivelGuardado;
	int puntuacionGuardada;
	int flechasGuardadas;
	bool victoriaGuardada;
	archivo >> tipo >> nivelGuardado >> puntuacionGuardada >> flechasGuardadas >> victoriaGuardada;
	if (!archivo || tipo != "Game")
	{
		throw FileFormatError("saved.txt", 1);
	}
	try
	{
		if (!loadLevel(to_string(level) + ".txt"))
		{
			throw FileNotFound(to_string(level) + ".txt");
		}
	}
	catch (const GameError&)
	{
		for (int i = 0; i < textures.size(); i++)
		{
			delete textures[i];
			textures[i] = nullptr;
		}

		throw;
	}
	archivo.ignore(numeric_limits<streamsize>::max(), '\n'); // Por los saltos de lineas que se quedaba sin saltar y me estaba dando demasiados problemas 
	level = nivelGuardado;
	puntuacion = puntuacionGuardada;
	arrows = flechasGuardadas;
	ganaste = victoriaGuardada;
	auto it = sceneobject.begin();
	int linea = 1;
	while (it != sceneobject.end())
	{
		delete* it;
		it = sceneobject.erase(it);
	}
	string contenido;
	while (getline(archivo, contenido)) // Super util te consigue tal cual la linea 
	{
		linea++;
		istringstream datos(contenido);

		string tipo;
		datos >> tipo;
		if (tipo == "Butterfly")
		{
			Butterfly* but = new Butterfly(this, datos, getTexture(BUTTERFLY), linea);
			addObject(but);
		}
		else if (tipo == "Balloon")
		{
			Balloon* bal = new Balloon(this, datos, getTexture(BALLOON), linea);
			addObject(bal);
		}
		else if (tipo == "Arrow")
		{
			Arrow* arrow = new Arrow(this, datos, getTexture(ARROW), linea);
			addObject(arrow);
		}
		else if (tipo == "Bow")
		{
			delete bow;
			bow = new Bow(this, datos, getTexture(BOW), linea);


		}
		else
		{
			for (auto it = sceneobject.begin(); it != sceneobject.end(); it++)
			{
				delete* it;
				it = sceneobject.erase(it);
			}
			if (bow != nullptr)
			{
				delete bow; 
			}
			throw FileFormatError("saved.txt", linea);
		}
	}
}			
void Game::RevisarMeta()
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
			

			list<SceneObject*>::iterator it = sceneobject.begin();

			while (it != sceneobject.end())
			{
				delete* it;
				it = sceneobject.erase(it);

			}

			GenerarMariposas();


		}
	}
}
Game::~Game()
{
	list<SceneObject*>::iterator it = sceneobject.begin();
	while (it != sceneobject.end())
	{
		delete* it;
		it = sceneobject.erase(it);
	}
	for (int i = 0; i < textures.size();i++)
	{
		delete textures[i];

	}

	delete bow;
	delete infoBar;
}

void Game::render() const //Preguntar a ruben porque hay que poner const tambien en el interador 
{

	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, Red, Green, Blue, 255);
	if (bow != nullptr)
	{
		bow->render();

	}

	for (auto it = gameobjetc.begin(); it != gameobjetc.end(); it++)
	{
		(*it)->render();
	}

	for (auto it = sceneobject.begin(); it != sceneobject.end(); it++)
	{
		(*it)->render();
	}

	infoBar->render(); 



	SDL_RenderPresent(renderer);
}
void Game::CreateBalloon()
{

	int color = std::uniform_int_distribution<int>(0, 5)(randomGenerator);
	int posx = std::uniform_int_distribution<int>(300, 700)(randomGenerator);
	float velocidad = std::uniform_real_distribution<float>(0.1f, 0.3f)(randomGenerator);
	Rectangle rectball(Point2D<>(posx, WINDOW_HEIGHT + 90), 90, 90);
	Balloon* bal = new Balloon(rectball, color, Point2D<>(0, -velocidad), getTexture(BALLOON), this);
	addObject(bal);


}
void Game::Quitarpuntuación(int point)
{
	if (puntuacion != 0)
	{
		puntuacion -= point;
	}
	NMariposa--;

}
void Game::DarPuntuacion(int mul)
{
	int extra = 0;
	if (mul > 1)
	{
		extra = 1 * mul; // Te sumo la cantidad de globos extras que has destruido con la misma flecha 
	}
	puntuacion += ballpoints * mul + extra;

}
void
Game::update()
{

	StartTime = SDL_GetTicks();
	infoBar->update(FRAME_PERIOD);
	for (auto it = gameobjetc.begin(); it != gameobjetc.end(); it++)
	{
		(*it)->update(FRAME_PERIOD);
	}
	TimeBalloons += FRAME_PERIOD;
	if (TimeBalloons >= baldelay)
	{
		CreateBalloon();
		TimeBalloons = 0;
	}
	// globos

	auto it = sceneobject.begin();
	while (it != sceneobject.end())
	{
		if (!(*it)->update(FRAME_PERIOD))
		{
			delete* it;
			it = sceneobject.erase(it);
		}
		else
		{
			it++;
		}
	}

	//arco
	if (!bow->update(FRAME_PERIOD)) exit = true;



	FrameTime = SDL_GetTicks() - StartTime;
	if (FrameTime < FRAME_PERIOD)
	{
		SDL_Delay(FRAME_PERIOD - FrameTime);
	}
	RevisarMeta();
	if (NMariposa == 0)
	{
		exit = true;
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

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_EVENT_QUIT)
		{
			exit = true;
		}
		else if (event.type == SDL_EVENT_KEY_DOWN)
		{
			if (event.key.key == SDLK_S &&
				(event.key.mod & SDL_KMOD_CTRL))
			{

				save();
			}
			else if (event.key.key == SDLK_O &&
				(event.key.mod & SDL_KMOD_CTRL))
			{

				cargar();
			}
		}


		if (bow->handleEvent(event))
		{
			arrows--;
		}
	}
}
int Game::nuevadir()
{
	return std::uniform_int_distribution<int>(-1, 1)(randomGenerator);

}
// bool
bool Game::checkCollision(const Rectangle& rect)
{


	auto it = sceneobject.begin();

	while (it != sceneobject.end() && !((*it)->hit(rect))) //Recorro hasta encontrar un globo con el que choque 
	{

		it++;
	}
	if (it != sceneobject.end())
	{

		return true;
	}
	return false;
}
bool Game::loadLevel(string archivo)
{
	int line = 0;
	ifstream archi(string(LEVEL_ROOT) + archivo);
	if (!archi)
	{
		return false;
	}
	string palabras;
	while (archi >> palabras)
	{
		line++;
		if (palabras[0] == '#') archi.ignore(1000, '\n');
		else if (palabras == "arrows")
		{
			archi >> arrows;

		}
		else if (palabras == "baldelay")
		{
			archi >> baldelay;

		}
		else if (palabras == "butterfly")
		{
			archi >> NMariposa;
		}
		else if (palabras == "goal")
		{
			archi >> goal;

		}
		else if (palabras == "balpoints")
		{
			archi >> ballpoints;

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
	return true;

}
int Game::getGoal() const { return goal; }
int Game::getArrows() const
{
	return arrows;
}
int Game::getPoint() const
{
	return puntuacion;
}
int Game::getBallPoint() const
{
	return ballpoints;
}
int Game::getPoints() const
{
	return puntuacion;
}

