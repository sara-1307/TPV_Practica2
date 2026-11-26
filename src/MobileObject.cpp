#include "MobileObject.h"

void MobileObject::SobreUpdate()
{

}

void MobileObject::EscribirDatos(std::ostream& archivo) const
{
    SceneObject::EscribirDatos(archivo);

    archivo << Speed.getX() << " " << Speed.getY() << " ";
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

    Speed.SetX(x);
    Speed.SetY(y);
}
MobileObject::MobileObject(Point2D<> Speed, Texture* tex, Rectangle rec, Game* game)
    : SceneObject(tex, rec, game), Speed(Speed)
{

}
