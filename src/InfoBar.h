#pragma once

#include "GameObject.h"
#include "SceneObject.h"

#include <vector>

using namespace std;
class InfoBar : public GameObject
{
private:
	std::vector<SceneObject*> v;
public:
	InfoBar(Game* game);
	~InfoBar();
	int getDigits();
	void render() const override;
	bool update(float delta) override;	
};

