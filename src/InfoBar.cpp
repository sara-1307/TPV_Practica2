#include "InfoBar.h"
#include "Puntuacion.h"
#include "Vidas.h"

InfoBar::InfoBar(Game* game) :GameObject(game)
{
	
	//Es la flecha menos 1 porque empezamos en 0 
	for (int i = 0; i < game->getArrows(); i++)
	{
		
		v.push_back(new Vidas(game, i));
	}

	for (int i = 0 ; i < getDigits();i++)
	{
		
		v.push_back(new Puntuacion(game, i));
	}
}
int InfoBar::getDigits()
{
	int aux = this->game->getGoal();
		int i = 0;
		while (aux != 0)
		{
			i++;
			aux = aux / 10;
		}
		return i;
}
InfoBar::~InfoBar()
{
	for (int i = 0; i < v.size(); i++)
	{
		delete v[i];
	}
}
bool InfoBar::update(float delta)
{
	for (int i = 0; i < v.size(); i++)
	{
		v[i]->update(delta);
	}
	return true;
}
void InfoBar::render() const
{
	for (int i = 0; i < v.size(); i++)
	{
		v[i]->render();
	}
}
void InfoBar::EscribirDatos(std::ostream&) const
{
}

