#pragma once
#include <string>
#include "GameError.h"
class FileNotFound : public GameError
{
public:
	using GameError::GameError;
	FileNotFound(const std::string& filename);
	//const char* what() const noexcept override;
};

