#include "player.h"

Player::Player()
{

}

vector<Item>* Player::getInventory()
{
    return &inventory;
}

void Player::putItemInInventory(Item *item)
{
    inventory.push_back(*item);
    checkWinCond();
}

QString Player::inventoryToString()
{
    QString tempString = "Items in the inventory:";
    int inventorySize = (inventory.size());

    if (inventorySize < 1)
        tempString = "The inventory is empty";
    else if (inventorySize > 0)
        for (int i = 0; i < inventorySize; i++) {
            tempString = tempString + "\n" + inventory[i].getName();
        }
    return tempString;
}

void Player::killPlayer()
{
    QMessageBox msgBox;
    msgBox.setText("You have died. Game Over!");
    msgBox.exec();
    exit(0);
}

bool Player::checkIfInInventory(QString itemName)
{
    int inventorySize = (inventory.size());
    bool found = false;
    if (inventorySize > 0) {
        for (int i = 0; i < inventorySize && !found; i++) {
            if (itemName.compare(inventory.at(i).getName()) == 0) {
                found = true;
            }
        }
    }
    return found;
}

void Player::winGame()
{
    QMessageBox msgBox;
    msgBox.setText("You have won the game!");
    msgBox.exec();
    exit(0);
}

void Player::checkWinCond()
{
    if (checkIfInInventory("OMG"))
        winGame();
}

void Player::destroyItem(QString itemName)
{
    bool found = false;
    for (int i = 0; i < inventory.size() && !found; i++) {
        Item* item = &inventory.at(i);
        if (itemName.compare(item->getName()) == 0) {
            found = true;
            delete item;
            inventory.erase(inventory.begin()+i);
        }
    }
}
