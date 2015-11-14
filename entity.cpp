#include "entity.h"

Entity::Entity(QString name, QString image, QRect geometry)
{
    this->name = name;
    this->image = image;
    this->geometry = geometry;
}

QString Entity::getName()
{
    return name;
}

QString Entity::getImage()
{
    return image;
}

QRect Entity::getGeometry()
{
    return geometry;
}

QString Entity::getType()
{
    return "entity";
}
