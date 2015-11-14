#ifndef ITEM_H
#define ITEM_H

#include <map>
#include <QString>
#include <QRect>
#include "entity.h"
using namespace std;

class Item :public Entity
{
public:
    Item (QString name, QString image = "itemNULL.gif", QRect geometry = QRect(100, 100, 50, 50));
    virtual QString getType();
};

#endif // ITEM_H
