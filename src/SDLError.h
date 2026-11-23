#pragma once
#include "GameError.h"
#include <string>
class SDLError :public GameError
{
public:
	using GameError::GameError;
	SDLError();
	//const char* what() const noexcept override;
};

