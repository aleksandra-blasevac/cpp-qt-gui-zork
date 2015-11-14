#include "gameplay.h"

Gameplay::Gameplay()
{
    createRooms();
}

void Gameplay::createRooms()
{
    Room *attic, *basement, *catRoom, *gate, *hallway, *kitchen, *landing, *livingRoom, *street;

    attic = new Room("You're in a room a", "map_attic.png", "roomA.gif");
    basement = new Room("You're in a room b", "map_basement.png", "roomB.gif");
    catRoom = new Room("You're in a room c", "map_catRoom.png", "roomC.gif");
    gate = new Room("You're in a room d", "map_gate.png", "room_gate.png");
    gate->addEntity(new Npc("Drunk Dude", "I'm soooo drunk....", "npc_DrunkDude.png", QRect(180, 150, 150, 235)));
    hallway = new Room("You're in a room e", "map_hallway.png", "room_hallway.png");
    kitchen = new Room("You're in a room f", "map_kitchen.png", "roomF.gif");
    landing = new Room("You're in a room g", "map_landing.png", "roomG.gif");
    livingRoom = new Room("You're in a room h", "map_livingRoom.png", "roomH.gif");
    street = new Room("You're in a room i", "map_street.png", "room_street.png");

//             (U, R, D, L)
    attic->setExits(NULL, NULL, landing, NULL);
    basement->setExits(kitchen, NULL, NULL, NULL);
    catRoom->setExits(NULL, NULL, NULL, landing);
    gate->setExits(NULL, street, NULL, NULL);
    hallway->setExits(landing, NULL, livingRoom, street);
    kitchen->setExits(NULL, NULL, basement, livingRoom);
    landing->setExits(attic, catRoom, hallway, NULL);
    livingRoom->setExits(hallway, kitchen, NULL, NULL);
    street->setExits(NULL, hallway, NULL, gate);

    attic->unlockAllDoor();
    basement->unlockAllDoor();
    catRoom->unlockAllDoor();
    gate->unlockAllDoor();
    hallway->unlockAllDoor();
    kitchen->unlockAllDoor();
    landing->unlockAllDoor();
    livingRoom->unlockAllDoor();
    street->unlockAllDoor();

        currentRoom = gate;
}

Room* Gameplay::getCurrentRoom()
{
    return currentRoom;
}

QString Gameplay::goRoom(int direction) {

    pair<Room*, QString> nextRoom = currentRoom->nextRoom(direction);

    if (nextRoom.first == NULL)
        return nextRoom.second;
    else {
        currentRoom = nextRoom.first;
        return currentRoom->getDescription();
    }
}

