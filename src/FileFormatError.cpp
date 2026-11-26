#include "FileFormatError.h"

FileFormatError::FileFormatError(string const& filename, int line) : GameError("Error en el archivo : " + filename + " En la linea " + std::to_string(line))
{
}
