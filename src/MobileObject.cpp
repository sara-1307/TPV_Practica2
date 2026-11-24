#include "MobileObject.h"
#include <ostream>
#include "SceneObject.h"

//MobileObject::MobileObject(){}
bool MobileObject::update(float delta)
{
	this->MobileObject::position.move(MobileObject::speed * delta);
	return true;
}
//void MobileObject::saveObj(std::ostream& output)
//{
//	SceneObject::saveObj(output);
//	output << this->speed.getX() << " " << this->speed.getY() << " ";
//}

void MobileObject::EscribirDatos(std::ostream& archivo) const
{
    SceneObject::EscribirDatos(archivo);

    archivo << speed.getX() << " " << speed.getY() << " ";
}
MobileObject::MobileObject(Game* game, std::istream& archivo,
    Texture* tex, int linea)
    : SceneObject(game, archivo, tex, linea)
{
    float x, y;

    if (!(archivo >> x >> y))
    {
        throw FileFormatError("saved.txt", linea);
    }

    speed.SetX(x);
    speed.SetY(y);
}
MobileObject::MobileObject(Point2D<> Speed, Texture* tex, Rectangle rec, Game* game)
    : SceneObject(tex, rec, game), speed(Speed)
{

}
