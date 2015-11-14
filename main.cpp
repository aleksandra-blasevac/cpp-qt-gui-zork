#include <QApplication>
#include "gameplay.h"
#include "gameWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    GameWindow gameWindow;
    gameWindow.show();

    return app.exec();
}

