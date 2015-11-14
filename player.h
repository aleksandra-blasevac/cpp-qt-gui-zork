#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "item.h"
#include <QMessageBox>


class Player
{
private:
    vector<Item> inventory;
    void checkWinCond();
public:
    Player();
    vector<Item>* getInventory();
    void putItemInInventory(Item* item);
    QString inventoryToString();
    void killPlayer();
    bool checkIfInInventory(QString itemName);
    void winGame();
    void destroyItem(QString itemName);
};

#endif // PLAYER_H
