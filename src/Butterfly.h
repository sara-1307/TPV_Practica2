#pragma once
#include "MobileObject.h"
#include "game.h"
#include <ostream>
class Butterfly: public MobileObject
{
protected:
	std::mt19937_64* randomGenerator;
	float dirChangeTimer;
	float dirChangeLimit;

	bool dead;
	float maxSpeed;
public:
	//Butterfly(Game* game);
	//Butterfly(Game* game, std::ifstream& input);s
	void render() const override;
	bool update(float delta);
	void setAnimDir();
	bool hit(const Rectangle& rect) override;
	//void saveObj(std::ostream& output) override;
};

