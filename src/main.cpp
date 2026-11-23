//
// Tecnología de la Programación de Videojuegos 1
// Facultad de Informática UCM
//
// Plantilla de proyecto con SDL
//

#include "game.h"
#include "GameError.h"
#include <SDL3_image/SDL_image.h>

int main(int argc, char* argv[])
{
	try
	{
		Game().run();
	}
	catch (GameError e)
	{
		SDL_Window* win = SDL_CreateWindow("ERROR", 1,  1, SDL_WINDOW_NOT_FOCUSABLE);
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", e.what(), win);
		SDL_DestroyWindow(win);
	}
	

	// TODO: manejar excepciones

	return 0;
}
