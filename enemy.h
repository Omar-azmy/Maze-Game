#ifndef ENEMY_H
#define ENEMY_H
#include <QObject>
#include <QGraphicsPixmapItem>

enum movementDirection{             //The enum is used to make direction handling smoother and more understandable
    up = 0,
    down = 1,
    left = 2,
    right = 3
};

class Enemy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Enemy(int, std::vector<std::vector<int>>&, QPoint );        //constructor
private:
    movementDirection direction;
    QPoint pos;
    void randDir();                 // generates a random number that will be used to determine the direction
    int block_size;
    int counter = 0;
    QTimer* timer;
    QTimer* coll_timer;
    std::vector<std::vector<int>>* grid;
    bool CanMove(int x, int y);     //Determines if a block is possible to move into from the grid - checks if the next block is not a wall


private slots:
    void move();            //function that moves the enemy

};

#endif // ENEMY_H
