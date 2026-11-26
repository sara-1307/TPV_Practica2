#pragma once
#include <stdexcept>

using namespace std;
class GameError : public std::logic_error
{
public:
	using std::logic_error::logic_error;
};

