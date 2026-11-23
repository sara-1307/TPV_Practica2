#pragma once

#include "SceneObject.h"
#include "game.h"
class Vidas: public SceneObject
{
private:
	int ArrowIndex;
public:
	Vidas(Game* game, int i);
	protected:
		bool update(float delta) override;
		void render() const override;

};

