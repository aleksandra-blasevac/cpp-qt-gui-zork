#include "npc.h"

Npc::Npc(QString name, QString dialog, QString image, QRect geometry, QString wantedItem, Item *reward)
    : Entity(name, image, geometry)
{
    this->dialog = dialog;
    this->wantedItem = wantedItem;
    this->reward = reward;
}

QString Npc::getType()
{
    return "npc";
}

QString Npc::getDialog()
{
    return dialog;
}

QString Npc::getWantedItem()
{
    return wantedItem;
}

Item* Npc::getReward()
{
    return reward;
}
