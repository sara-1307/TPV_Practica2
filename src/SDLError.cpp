#include "SDLError.h"
#include <SDL3_image/SDL_image.h>

SDLError::SDLError() :GameError(("SDL ERROR : " + std::string(SDL_GetError())).c_str()) {}



