#ifndef ENTITY_H
#define ENTITY_H

#include <QString>
#include <QRect>


class Entity
{
private:
    QString name;
    QString image;
    QRect geometry;

public:
    Entity(QString name, QString image, QRect geometry);
    QString getName();
    QString getImage();
    QRect getGeometry();
    virtual QString getType();
};

#endif // ENTITY_H
