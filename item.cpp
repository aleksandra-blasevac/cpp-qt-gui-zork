#include "item.h"

Item::Item(QString name, QString image, QRect geometry)
    :Entity(name, image, geometry)
{
}

QString Item::getType()
{
    return "item";
}
