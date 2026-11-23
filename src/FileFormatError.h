#pragma once
#include <string>
#include "GameError.h"
class FileFormatError: public GameError
{
public:

	using GameError::GameError;
	FileFormatError(const std::string& filename,int line);
	//const char* what() const noexcept override;
};

