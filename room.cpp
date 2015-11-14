#include "room.h"

Room::Room(QString description, QString mapImageFile, QString roomImageFile)
{
    this->description = description;
    this->mapImageFile = mapImageFile;
    this->roomImageFile = roomImageFile;
}

QString Room::getDescription()
{
    return description;
}

void Room::setDescription(QString newDescription)
{
    description = newDescription;
}

QString Room::getMapImage()
{
    return mapImageFile;
}

QString Room::getRoomImage()
{
    return roomImageFile;
}

void Room::setExits(Room *north, Room *east, Room *south, Room *west)
{
    exits[NORTH] = north;
    exits[EAST] = east;
    exits[SOUTH] = south;
    exits[WEST] = west;
}

void Room::unlockAllDoor()
{
    locks[NORTH] = make_pair(false, NULL);
    locks[EAST] = make_pair(false, NULL);
    locks[SOUTH] = make_pair(false, NULL);
    locks[WEST] = make_pair(false, NULL);
}

void Room::setLock(int direction, bool locked, QString key)
{
    locks[direction] = make_pair(locked, key);
}

pair<Room*, QString> Room::nextRoom(int direction)
{
    Room* next = exits[direction];
    QString message = NULL;

    QString sDirect;
    switch (direction) {
    case NORTH:
        sDirect = "up";
        break;
    case SOUTH:
        sDirect = "down";
        break;
    case WEST:
        sDirect = "left";
        break;
    case EAST:
        sDirect = "right";
        break;
    default:
        sDirect = "";
        break;
    }

    if (next == NULL)        
        message = "There's no door " + sDirect + " from here.";
    else if (locks[direction].first) {
        next = NULL;
        QString key = locks[direction].second;
        message = "The door to the " + sDirect + " is locked.";
        if (key == NULL) {
            message += " It looks like it can be opened with a strong kick. You kicked the door open.";
            setLock(direction, false, NULL);
        }
        else {
            message += " You can open it with " + key;
        }
    }

    return make_pair(next, message);
}

void Room::addEntity(Entity *inEntity) {
    entitiesInRoom.push_back(&*inEntity);
}

vector<Entity*>* Room::getEntitiesVector()
{
    return &entitiesInRoom;
}

void Room::removeEntityFromRoom(int location)
{
    entitiesInRoom.erase(entitiesInRoom.begin()+location);
}

pair<bool, QString> Room::getLocks()
{
    return *locks;
}

void Room::destroyEntity(QString entityName)
{
    bool found = false;
    for (int i = 0; i < entitiesInRoom.size() && !found; i++) {
        Entity* entity = entitiesInRoom.at(i);
        if (entityName.compare(entity->getName()) == 0) {
            found = true;
            delete entity;
            removeEntityFromRoom(i);
        }
    }
}
