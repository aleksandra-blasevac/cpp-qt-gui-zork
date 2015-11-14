#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <QString>
#include "room.h"
#include <QApplication>

class Gameplay
{

private:
    Room *currentRoom;
    void createRooms();

public:
    Gameplay();
    Room* getCurrentRoom();
    QString goRoom(int direction);
};

#endif // GAMEPLAY_H
