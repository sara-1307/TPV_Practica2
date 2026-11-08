#pragma once


class Game;
class GameObject 
{
protected: 
	Game* game; 

public: 

	virtual void render() const = 0; 
	virtual bool update(float delta)  = 0;  // Cuando es virtual significa que el hijo tieene que incializar el metodo sin embargo no significa que cosas como lo que devuelve (en este caso bool) o el parametro que se pasa se modifiquen estos deben coincidir 

};


