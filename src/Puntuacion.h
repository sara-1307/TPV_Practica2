#pragma once
#include "rectangle.h"
#include "texture.h"
#include "game.h"
class Puntuacion :public SceneObject
{
private:
	int index;
public:
	Puntuacion(Game* game,int i);
	bool update(float delta) override;
	void render() const override;
	int getDigit();
};

