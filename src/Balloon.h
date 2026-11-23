#pragma once
#include "MobileObject.h"
#include "game.h"
#include <ostream>
#include <random>
class Balloon : public MobileObject
{
private:
	bool exploding;
	int FrameAnimation; // El  frame en el que estoy
	float TimeAnimation; // el tiempo de la animacion
	float TimeFrame; // el tiempo del frame
	int balspeed;
	int Combo;
	SceneObject* hitObj;

public:
	Balloon(Game* game);
	Balloon(Game* game, std::ifstream& input);
	virtual bool hit(const Rectangle& rect) override;
	bool update(float delta) override;
	bool getExploding() const;  // nos permite saber si ese globo ha esplotado es decir el jugador lo revento
	void saveObj(std::ostream& output) override;
};

