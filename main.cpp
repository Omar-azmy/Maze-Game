#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "player.h"
#include "map.h"
#include "customscene.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CustomScene* scene = new CustomScene;

    int block_size = 50;
    int grid_size = 15;

    QGraphicsView * view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view->show();
    view->setFixedSize(block_size * grid_size,block_size * grid_size);
    return a.exec();
}
