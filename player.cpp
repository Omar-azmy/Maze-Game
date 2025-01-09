#include "player.h"

Player::Player(): QGraphicsPixmapItem(),QObject()       //constructor that defines the pixmap of the player
{
    setPixmap(QPixmap(":/Images/Images/Player.png").scaled(50,50));

}


