#include "enemy.h"
#include "player.h"
#include <QMessageBox>
#include <QApplication>
#include <QTimer>
#include <QRandomGenerator>
#include <QGraphicsScene>


Enemy::Enemy(int b_size, std::vector<std::vector<int>>& G, QPoint position) : QGraphicsPixmapItem(QPixmap(":/Images/Images/Enemy.png").scaled(b_size,b_size)){      //constructor
    pos = position;
    block_size = b_size;
    grid = &G;
    timer = new QTimer();

    setPos(pos.x() * block_size, pos.y() * block_size);
    randDir();

    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(10);

}

void Enemy::randDir() //creates a random number to directly select the direction of movement of enemy
{
    int rand_num = QRandomGenerator::global()->bounded(4);

    switch(rand_num) {
    case 0:
        direction = up;
        break;
    case 1:
        direction = down;
        break;
    case 2:
        direction = left;
        break;
    case 3:
        direction = right;
        break;
    }
}

void Enemy::move()      //move enemy function
{
    counter++;    // to make the timer's time fast (for responsiveness) but keeping the movement of the enemies slow

    // End game if enemy collided with enemy
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(QGraphicsItem* item : colliding_items) {
        if(Player* player = dynamic_cast<Player*>(item)) {
            if(scene()) {
                scene()->removeItem(player);
                delete player;
                QMessageBox msgBox;
                msgBox.setWindowTitle("Game Over!!!");
                msgBox.setText("You Died :( ");
                msgBox.setStandardButtons(QMessageBox::Ok);
                msgBox.setDefaultButton(QMessageBox::Ok);
                msgBox.exec();
                QApplication::exit(1);
            }
        }
    }

    if(counter % 10 == 0){
    bool hitWall = true;

    switch(direction) {
    case up:
        if(CanMove(pos.y() - 1, pos.x())) {
            pos.setY(pos.y() - 1);
            hitWall = false;
        }
        break;
    case down:
        if(CanMove(pos.y() + 1, pos.x() )) {
            pos.setY(pos.y() + 1);
            hitWall = false;
        }
        break;
    case right:
        if(CanMove(pos.y(), pos.x() + 1)) {
            pos.setX(pos.x() + 1);
            hitWall = false;
        }
        break;
    case left:
        if(CanMove(pos.y(), pos.x()  - 1)) {
            pos.setX(pos.x() - 1);
            hitWall = false;
        }
        break;
    }

    if(hitWall){
        randDir();
        move();
    }
    else
        setPos(pos.x() * block_size, pos.y() * block_size);
    }
}
\
    bool Enemy::CanMove(int x, int y)             //checks if the enemy can move in to the determined block
{
    return  y >= 0 && y < grid->size() && x >= 0 && x < grid->size() && (*grid)[x][y] == 0;
}
