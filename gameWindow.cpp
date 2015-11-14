#include "gameWindow.h"
#include "ui_GameWindow.h"

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);


    player.putItemInInventory(new Item("torch"));
    printText("Welcome! " + gameplay.getCurrentRoom()->getDescription());
    ui->mapLabel->setScaledContents(true);
    refreshMap();
    ui->roomLabel->setScaledContents(true);
    refreshRoom();
    createEntityButtons();
    placeEntities();
    createInventoryButtons();
    showInventory();
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::refreshMap()
{
    Room *room = gameplay.getCurrentRoom();
    QImage image("../What/images/" + room->getMapImage());
    ui->mapLabel->setPixmap(QPixmap::fromImage(image));
}

void GameWindow::refreshRoom()
{
    Room *room = gameplay.getCurrentRoom();
    QImage image("../What/images/" + room->getRoomImage());
    ui->roomLabel->setPixmap(QPixmap::fromImage(image));
}

void GameWindow::on_lookAroundButton_clicked()
{
    Room *room = gameplay.getCurrentRoom();
    printText(room->getDescription());
}

void GameWindow::printText(QString text)
{
    ui->outputConsole->setText(text);
}

void GameWindow::placeEntities()
{
    setEntitiesButtonsInvisible(3);
    Room *room = gameplay.getCurrentRoom();
    vector<Entity*>* entities = room->getEntitiesVector();

    for (int i = 0; i < entities->size(); i++) {
            entityButtons[i]->setVisible(true);
            entityButtons[i]->setGeometry(entities->at(i)->getGeometry());
            entityButtons[i]->setIcon(QIcon("../What/images/" + entities->at(i)->getImage()));
            entityButtons[i]->setIconSize(entities->at(i)->getGeometry().size());
    }
}

void GameWindow::changeRoom(int direction)
{
    printText(gameplay.goRoom(direction));
    refreshMap();
    refreshRoom();
    placeEntities();
}

void GameWindow::useItem(int itemIndex)
{
    Room* room = gameplay.getCurrentRoom();
    pair<bool, QString> locks[4] = room->getLocks();
    vector<Item>* inventory = player.getInventory();
    QString itemClicked = inventory->at(itemIndex).getName();
    bool unlocked = false;

    QString text = "You can't use " + itemClicked + " right now";
    for (int i = 0; i < 4 && !unlocked; i++)
    {
        if (itemClicked == locks[i].second)
        {
            text = "Opened door using " + itemClicked;
            player.destroyItem(itemClicked);
            room->setLock(i, false);
            unlocked = true;
        }
    }
    if (!unlocked)
    {
        bool given = false;
        vector<Entity*>* entitiesInRoom = room->getEntitiesVector();

        for (int i = 0; i < entitiesInRoom->size() && !given; i++)
        {
            Entity* temp = entitiesInRoom->at(i);
            if (temp->getType() == "npc") {
                Npc* npc = static_cast<Npc*>(temp);
                if (itemClicked == npc->getWantedItem()) {
                    text = "You gave " + itemClicked + " to " + npc->getName() + ". He gave you "
                          + npc->getReward()->getName() + " in return and disappeared.";
                    player.putItemInInventory(npc->getReward());
                    room->destroyEntity(npc->getName());
                    given = true;
                    player.destroyItem(itemClicked);
                    placeEntities();
                }
            }
        }
    }

    printText(text);
}

void GameWindow::on_goNorthButton_clicked()
{
    changeRoom(NORTH);
}

void GameWindow::on_goSouthButton_clicked()
{
    changeRoom(SOUTH);
}

void GameWindow::on_goWestButton_clicked()
{
    changeRoom(WEST);
}

void GameWindow::on_goEastButton_clicked()
{
    changeRoom(EAST);
}

void GameWindow::on_killButton_clicked()
{
    player.killPlayer();
}

void GameWindow::createEntityButtons()
{
    QPushButton* imageButton1 = new QPushButton(this);
    connect(imageButton1, SIGNAL (clicked()), this, SLOT (entityButton1_clicked()));
    QPushButton* imageButton2 = new QPushButton(this);
    connect(imageButton2, SIGNAL (clicked()), this, SLOT (entityButton2_clicked()));
    QPushButton* imageButton3 = new QPushButton(this);
    connect(imageButton3, SIGNAL (clicked()), this, SLOT (entityButton3_clicked()));

    entityButtons[0] = imageButton1;
    entityButtons[1] = imageButton2;
    entityButtons[2] = imageButton3;
}

void GameWindow::createInventoryButtons()
{
    QPushButton* invButton1 = new QPushButton(this);
    invButton1->setGeometry(970, 490, 45, 45);
    connect(invButton1, SIGNAL (clicked()), this, SLOT (invButton1_clicked()));

    QPushButton* invButton2 = new QPushButton(this);
    invButton2->setGeometry(1040, 490, 45, 45);
    connect(invButton2, SIGNAL (clicked()), this, SLOT (invButton2_clicked()));

    QPushButton* invButton3 = new QPushButton(this);
    invButton3->setGeometry(1110, 490, 45, 45);
    connect(invButton3, SIGNAL (clicked()), this, SLOT (invButton3_clicked()));

    invButtons[0] = invButton1;
    invButtons[1] = invButton2;
    invButtons[2] = invButton3;
}

void GameWindow::setEntitiesButtonsInvisible(int numberOfButtons)
{
    for (int i = 0; i < numberOfButtons; i++) {
        entityButtons[i]->setVisible(false);
    }
}

void GameWindow::interactWithEntity(int index)
{
    Room *room = gameplay.getCurrentRoom();
    vector<Entity*>* entities = room->getEntitiesVector();
    Entity* temp = entities->at(index);

    if (temp->getType() == "item") {
        Item* item = static_cast<Item*>(temp);
        printText("You have picked up " +  item->getName());
        player.putItemInInventory(item);
        room->removeEntityFromRoom(index);
        placeEntities();
        showInventory();
    }
    else if (temp->getType() == "npc") {
        Npc* npc = static_cast<Npc*>(temp);
        printText(npc->getName() + " said: " + npc->getDialog());
    }
    else
        printText("Something is wrong with this entity - " + temp->getType());
}

void GameWindow::entityButton1_clicked()
{
    interactWithEntity(0);
}

void GameWindow::entityButton2_clicked()
{
    interactWithEntity(1);
}

void GameWindow::entityButton3_clicked()
{
    interactWithEntity(2);
}

void GameWindow::resetAllInvButtons(int amountButtons)
{

    for (int i = 0; i < amountButtons; i++) {
         invButtons[i]->setEnabled(false);
         invButtons[i]->setIcon(QIcon());
    }
}

void GameWindow::showInventory()
{
    resetAllInvButtons(3);
    vector<Item>* inventory = player.getInventory();

    for (int i = 0; i < inventory->size(); i++)
    {
        invButtons[i]->setEnabled(true);
        invButtons[i]->setIcon(QIcon("../What/images/" + inventory->at(i).getImage()));
        invButtons[i]->setIconSize(QSize(45, 45));
    }
}

void GameWindow::invButton1_clicked()
{
    useItem(0);
    showInventory();
}

void GameWindow::invButton2_clicked()
{
    useItem(1);
    showInventory();
}

void GameWindow::invButton3_clicked()
{
    useItem(2);
    showInventory();
}
