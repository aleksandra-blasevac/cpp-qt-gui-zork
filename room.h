#ifndef ROOM_H
#define ROOM_H

#include <map>
#include <QString>
#include <vector>
#include "item.h"
#include "npc.h"
using namespace std;
#include <utility> //for pair

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3



class Room
{

private:
    QString description;
    QString mapImageFile;
    QString roomImageFile;
    Room* exits[4];
    pair<bool, QString> locks[4];
    vector<Entity*> entitiesInRoom;


 public:
    Room(QString description, QString mapImageFile = "mapNull.gif", QString roomImageFile = "roomNull.gif");
    void setExits(Room *north, Room *east, Room *south, Room *west);
    void unlockAllDoor();
    void setLock(int direction, bool locked, QString key = NULL);
    pair<bool, QString> getLocks();
    QString getDescription();
    void setDescription(QString newDescription);
    QString getMapImage();
    QString getRoomImage();
    pair<Room*, QString> nextRoom(int direction);
    void addEntity(Entity *inEntity);
    vector<Entity *> *getEntitiesVector();
    void removeEntityFromRoom(int location);
    void destroyEntity(QString entityName);
};

#endif // ROOM_H
