#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <vector>
#include <QKeyEvent>
#include "map.h"
#include "player.h"


class CustomScene : public QGraphicsScene       //this is the custom scene where I add all needed elements for easier implementation
{
public:
    CustomScene();          //constructor
private:
    Player * player;
    void createPath();         //creates the visual shortest path the player needs to go to the goal
    void deletePath();         //deletes the shortest path visually to be re-drawn when the player moves
    map myMap;
    std::vector<std::vector<int>> grid;
    int block_size = 50;
    int grid_size = 15;
    QGraphicsPixmapItem* goal;
protected:
    void keyPressEvent(QKeyEvent * event);      //The fucntion that responds to keys - for movement

};

#endif // CUSTOMSCENE_H
