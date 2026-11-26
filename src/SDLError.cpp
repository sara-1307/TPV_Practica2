#include "SDLError.h"
SDLError::SDLError() : GameError(SDL_GetError()) {};
