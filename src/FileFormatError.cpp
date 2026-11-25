#include "FileFormatError.h"

FileFormatError::FileFormatError(
    const std::string& archivo,
    int line)
    : GameError(
        ("Error en el archivo: " + archivo +
         " en la línea " + std::to_string(line)).c_str())
{
}

