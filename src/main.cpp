//
// Tecnología de la Programación de Videojuegos 1
// Facultad de Informática UCM
//
// Plantilla de proyecto con SDL
//

#include "game.h"

int main(int argc, char* argv[])
{
	try
	{
		Game().run();
	}
	catch (const string& error)
	{
		std::cout << error << endl;
	}
	

	// TODO: manejar excepciones

	return 0;
}
