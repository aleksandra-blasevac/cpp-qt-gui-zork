#ifndef NPC_H
#define NPC_H

#include "entity.h"
#include "item.h"

class Npc : public Entity
{
private:
    QString dialog;
    QString wantedItem;
    Item* reward;
public:
    Npc(QString name, QString dialog = "I don't want to talk with you!", QString image = "npcNULL.gif",
        QRect geometry = QRect(100, 100, 50, 50), QString wantedItem = NULL, Item* reward = NULL);
    virtual QString getType();
    QString getDialog();
    QString getWantedItem();
    Item* getReward();
};

#endif // NPC_H
