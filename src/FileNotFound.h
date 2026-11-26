#pragma once
#include "GameError.h"
class FileNotFound : public GameError
{
public:
	FileNotFound(string const& filename);
};

