#include "GameError.h"

GameError::GameError(const char* what_arg):std::logic_error(what_arg) {}

