#include "game.h"

#include <string>

#include <SDL3_image/SDL_image.h>

#include "texture.h"
 #include <vector>
#include "Balloon.h"
#include <random>
#include <algorithm>


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
	{"arrow.png"},{"balloons.png",7,6},{"Dance.png", 1,8},{"digits.png",1,10},
};

Game::Game()
  : exit(false),
	randomGenerator(std::random_device{}())
{
	// Carga SDL y crea la ventana con su renderizador
	if (!SDL_Init(SDL_INIT_VIDEO))
		throw "SDL_Init: "s + SDL_GetError();

	if (!SDL_CreateWindowAndRenderer(WINDOW_TITLE,
	                                 WINDOW_WIDTH, WINDOW_HEIGHT,
	                                 0, &window, &renderer))
		throw "window or renderer: "s + SDL_GetError();

	// Carga las texturas al inicio
	try {
		textures.fill(nullptr);
		string imgRoot = IMAGE_ROOT;

		for (size_t i = 0; i < textures.size(); i++) {
			auto [name, nrows, ncols] = textureList[i];
			textures[i] = new Texture(renderer, (imgRoot + name).c_str(), nrows, ncols);
		}
	}
	catch (const string& error) {
		std::cout << error << endl;
		for (int i = 0; i < textures.size();i++)
		{
			delete textures[i];

		}
		throw error; // relanza la excepción
	}

	// Configura que se pueden utilizar capas translúcidas
	// SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	if(!(loadLevel((to_string(level) + ".txt"))))
	{
		for (int i = 0; i < textures.size();i++)
		{
			delete textures[i];

		}
		throw string("Error: no se encuentra el fichero de configuracion: " );
	}
	
	

	Rectangle rectArco(Point2D<>(100, 100), 100,100);
	bow = new Bow(rectArco, getTexture(BOW), Point2D<>(1, 0),arrows, true, Point2D<>(0, 0));
	cont =  deltatime =  puntuacion = TimeBalloons = 0; // Se que deltatime no lo uso es porque quiero preguntarle algo a Rubén y lo dejo para cuando lo pregunte
	infoBar = new InfoBar (getTexture(DIGITS), getTexture(ARROW), getTexture(DANCE), arrows, to_string(goal));
	
	
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
			infoBar->PuntosProsimoNivel(to_string(goal), getTexture(DIGITS));
			for (int i = 0; i < balloon.size();i++)
			{
				Eliglob(balloon, i);
			}
			for (int i = 0; i < arrow.size();i++)
			{
				Eliarrow(arrow, i);
			}
		}
	}
}
Game::~Game()
{
	
		for (int i = 0; i < balloon.size();i++)
		{
			delete balloon[i];
		}
		std::cout << " borrado todos los globos" << std::endl;

		for (int i = 0; i < arrow.size();i++)
		{
			delete arrow[i];
			
		}
		std::cout << " borrado todas las  flechas"<< std::endl;

		for (int i = 0; i < textures.size();i++)
		{
			delete textures[i];
			
		}
		std::cout << " borrado todos las texturas" << std::endl;
	delete bow; 
	delete infoBar;
}

void Game::render() const
{
	
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, Red, Green, Blue, 255); 
	if (bow != nullptr)
	{
		bow->render();

	}
	if (infoBar != nullptr)
	{
		infoBar->render();
	}
	
	for (int i = 0; i < balloon.size();i++) 
	{
			balloon[i]->render();
	}
	
	
	for (int i = 0; i < arrow.size(); i++)
	{
			arrow[i]->render();
		
	}
	
	
	

	SDL_RenderPresent(renderer);
}
void Game::CreateBalloon() // preguntar
{
	std::cout << "generando globo";
	 int color = std::uniform_int_distribution<int>(0, 5)(randomGenerator);
	 int posx = std::uniform_int_distribution<int>(300, 700)(randomGenerator);
	 float velocidad = std::uniform_real_distribution<float>(-1, -0.3)(randomGenerator); //SARA NO SABE USAR FLOAAAAAAAT // USO un INT PARA ESTOOOOOOOOOOO
	 Rectangle rectball(Point2D<>(posx,800), 90, 90);
	 Balloon* bal = new Balloon(rectball, color, Point2D<>(0, velocidad), getTexture(BALLOON));
	 balloon.push_back(bal);
	

}
void Game::Eliglob(std::vector<Balloon*>& bal, int i) //Como el orden de los globos en el vector no importa puedo cambair el ultimo con el final y  reducir el vector
{
	if (bal[i]->getexploto())
	{
		puntuacion += ballpoints; 
		infoBar->updatepoint(puntuacion);
	}
	swap(bal[i], bal[bal.size() - 1]); // A alex no le gusta esta maravilla
	delete bal[bal.size() - 1]; 
	bal.pop_back();
}
void Game::Eliarrow(std::vector<Arrow*>& arrow, int i)
{
	
	swap(arrow[i], arrow[arrow.size() - 1]); 
	delete arrow[arrow.size() - 1];
	arrow.pop_back();
}
void
Game::update()
{
	StartTime = SDL_GetTicks();
	infoBar->update(arrows, getTexture(ARROW), FRAME_PERIOD);
	TimeBalloons += FRAME_PERIOD; 
	if (TimeBalloons >=baldelay )
	{
		CreateBalloon();
		TimeBalloons = 0;
	}
	// globos
	int i = 0; 
	while (i < balloon.size())
	{
		if (!balloon[i]->update(FRAME_PERIOD)) Eliglob(balloon, i);
		else
		{
			i++;
		}
	}
	cont++;
	//arco
	if (!bow->update(FRAME_PERIOD) && arrow.empty()) exit = true;
	
	//flechas
	i = 0; 
	while (i<arrow.size())
	{
		if (!(arrow[i]->update(FRAME_PERIOD)))
		{
			Eliarrow(arrow, i);
		}
		else
		{
			i++;
		}
	}
	FrameTime = SDL_GetTicks() - StartTime;
	if (FrameTime < FRAME_PERIOD)
	{
		SDL_Delay(FRAME_PERIOD - FrameTime);
	}
	RevisarMeta(); 
}


void Game::run()
{
	//double ultip = SDL_GetTicks();  // Preguntan a ruben 
	while (!exit) {
		//double tiempoactual = SDL_GetTicks();
	   // deltatime = (tiempoactual - ultip) / 1000.0f;
		//ultip = tiempoactual; 
		
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
			exit = true;
		else
		{
			if (bow->handleEvent(event))  // Devuelve true cuando tiene que crear una flecha
			{
				Point2D posflecha = bow->getposmed(); 
				Rectangle rec(posflecha, 100, 20);
				Arrow* flecha = new Arrow(this, getTexture(ARROW), rec, Point2D<>(1, 0));
				arrow.push_back(flecha);
				infoBar->updatelife();
				arrows--;
			}
		}
			

		
	}
}

// bool
bool Game::checkCollision(const Rectangle& rect)
{

	int i = 0;
	while (i<balloon.size() &&!(balloon[i]->hit(rect))) //Recorro hasta encontrar un globo con el que choque
	{
		i++;
	}
	if (i != balloon.size())
	{
		
		return true;
	}
	return false;
 }
bool Game::loadLevel(string archivo)
{
	ifstream archi(string(LEVEL_ROOT) +  archivo);
	if (!archi)
	{
		return false;
	}
	string palabras; 
	while (archi >> palabras)
	{
		if (palabras[0] == '#') archi.ignore(1000, '\n');
		else if (palabras == "arrows")
		{
			if (!(archi >> arrows))
			{
				throw string("Error: valor incorrecto para arrows" ); archi.close();
			}
		}
		else if (palabras == "baldelay")
		{
			if (!(archi >> baldelay))
			{
				throw string("Error: valor incorrecto para baldelay"); archi.close();
			}
		}
		else if (palabras == "goal")
		{
			if (!(archi >> goal))
			{
				throw string("Error: valor incorrecto para goal"); archi.close();
			}
		}
		else if (palabras == "balpoints")
		{
			if (!(archi >> ballpoints))
			{
				throw string("Error: valor incorrecto para ballpoinr"); archi.close();
			}
		}
		else if (palabras == "bgcolor")
		{
			if (!(archi >> Red >>Green>>Blue))
			{
				throw string("Error: valor incorrecto para bgcolor"); archi.close();
			}
		}
		else
		{
			archi.close(); throw string("Error: Parametro no encontrado");
		}
	}
	archi.close();
	return true;
}

