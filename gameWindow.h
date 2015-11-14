#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QString>
#include "gameplay.h"
#include "item.h"
#include <QPushButton>
#include "player.h"
#include "npc.h"

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();
    void printText(QString text);

private slots:

    void on_lookAroundButton_clicked();

    void on_goNorthButton_clicked();

    void on_goSouthButton_clicked();

    void on_goWestButton_clicked();

    void on_goEastButton_clicked();

    void on_killButton_clicked();

    void entityButton1_clicked();

    void entityButton2_clicked();

    void entityButton3_clicked();

    void invButton1_clicked();

    void invButton2_clicked();

    void invButton3_clicked();

private:
    Ui::GameWindow *ui;
    Gameplay gameplay;
    Player player;
    void refreshMap();
    void refreshRoom();
    void changeRoom(int direction);
    void placeEntities();
    void useItem(int itemIndex);
    QPushButton* entityButtons[3];
    QPushButton* invButtons[3];
    void createEntityButtons();
    void setEntitiesButtonsInvisible(int numberOfButtons);
    void interactWithEntity(int index);
    void showInventory();
    void createInventoryButtons();
    void resetAllInvButtons(int amountButtons);

};

#endif // GAMEWINDOW_H
