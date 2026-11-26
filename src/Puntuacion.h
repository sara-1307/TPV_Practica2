#pragma once
#include "rectangle.h"
#include "SceneObject.h"
#include "texture.h"
class Puntuacion : public SceneObject
{

private:

	int frame;
public:
	Puntuacion(Texture* tex, Rectangle pos, Game* game);
	void update(int pos);
	bool update(float delta) override;
	void render() const override;
	void Change(int pos);
};

