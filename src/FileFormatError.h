#pragma once
#include "GameError.h"
#include <sstream>
class FileFormatError : public GameError
{
public:
	FileFormatError(string const& filename, int line);
};



