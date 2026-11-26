#include "FileNotFound.h"

FileNotFound::FileNotFound(string const& filename) : GameError("No se ha encontrado el archivo: " + filename) {};
