#pragma once
#include <stdexcept>
#include <string>
class GameError : public std::logic_error
{
	public:
	//Esto hace que heredemos el constructor del padre directamente
	using std::logic_error::logic_error;
	GameError(const char* what_arg);
	//const char* what() const noexcept override;
	
};

