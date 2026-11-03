#include "InfoBar.h"

InfoBar::InfoBar(Texture* texpunt, Texture* texvidas, Texture* texdance, int flechas, string objetivo)
{
	dance = Dance(texdance, Rectangle(Point2D<>(0, 500), 100, 100)); // preguntar
	for (int i = 0; i < flechas;i++)
	{
		Rectangle pos(Point2D<>(20 + i * 35, 20), 30, 30);
		Lifes.emplace_back(texvidas, pos); //emplate en vez de push back porque con el pushback tengo que crear el objeto y meterselo y esto es directo y me encanta 
	}
	for (int i = 0; i < objetivo.size(); i++)
	{
		Rectangle pos(Point2D<>(650 + i * 30, 20), 25, 35);

		Point.emplace_back(texpunt, pos);
		Point.back().Change(0); //le meto 0 al principio
	}
}
void InfoBar::update( int arrows, Texture* texvidas, float delta)
{

	while (Lifes.size() < arrows)
	{
		int i = Lifes.size();
		Rectangle pos(Point2D<>(20 + i * 35, 20), 30, 30);
		Lifes.emplace_back(texvidas, pos);
	}

	while (Lifes.size() > arrows)
	{
		Lifes.pop_back();
	}
	dance.update(delta);
}
void InfoBar::render() const
{
	for (int i = 0; i < Lifes.size();i++)
	{
		Lifes[i].render();
	}
	for (int i = 0; i < Point.size();i++)
	{
		Point[i].render();
	}
	//dance.render(); // Hay cierta gente que cree que poner a una chavala bailando no anima el videojeugo YO creo que es clave
}

void InfoBar::updatelife()
{
	if (!Lifes.empty())
	{
		Lifes.pop_back();
	}
}
void InfoBar::updatepoint(int point)
{
	int numero = point;

	for (int i = Point.size() - 1; i >= 0; i--)
	{
		int digito = numero % 10;
		Point[i].Change(digito);
		numero /= 10;
	}
}
void InfoBar::PuntosProsimoNivel(string objetive, Texture* texpunt)
{
	while (Point.size() < objetive.size())
	{
		int i = Point.size();
		Rectangle pos(Point2D<>(650 + i * 30, 20), 25, 35);

		Point.emplace_back(texpunt, pos);
		Point.back().Change(0);
	}

	while (Point.size() > objetive.size())
	{
		Point.pop_back();
	}

	updatepoint(0);
}


