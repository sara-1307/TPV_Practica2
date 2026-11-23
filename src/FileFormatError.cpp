#include "FileFormatError.h"

FileFormatError::FileFormatError(const std::string& filename, int line):GameError(("Error en linea "+line+std::string(" del archivo "+filename)).c_str()){ }
