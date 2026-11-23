#include "FileNotFound.h"

FileNotFound::FileNotFound(const std::string& filename) :GameError(("Error, archivo " + filename + " no encontrado").c_str()){}
