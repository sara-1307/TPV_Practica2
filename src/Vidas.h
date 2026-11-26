#pragma once
#include "rectangle.h"
#include "texture.h"
#include "SceneObject.h"
class Vidas : public SceneObject
{
private:

public:
	Vidas(Texture* tex, Rectangle pos, Game* game);
	void render() const override;
	bool update(float delta) override;

};

