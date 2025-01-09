#ifndef PLAYER_H
#define PLAYER_H
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QKeyEvent>

class Player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Player();           //constructor
};

#endif // PLAYER_H
