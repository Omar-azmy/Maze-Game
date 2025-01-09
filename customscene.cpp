#include "customscene.h"
#include "enemy.h"
#include "path.h"
#include <QMessageBox>
#include <QApplication>

CustomScene::CustomScene() {        //constructor

    // add player and goal to the scene
       player = new Player();
       goal = new QGraphicsPixmapItem(QPixmap((":/Images/Images/Target.png")).scaledToWidth(block_size));

      player->setPos(block_size,block_size);
      player->setZValue(100);
      addItem(player);
      goal->setPos(block_size * (grid_size - 3),block_size * (grid_size - 1));
      goal->setZValue(100);
      addItem(goal);

    //make player focusable
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    //creating and adding enemies to the scene
    Enemy* enemy1 = new Enemy(block_size, grid, QPoint(10,5));
    Enemy* enemy2 = new Enemy(block_size, grid, QPoint(3,12));
    Enemy* enemy3 = new Enemy(block_size, grid, QPoint(4,5));
    addItem(enemy1);
    enemy1->setZValue(6);
    addItem(enemy2);
    enemy2->setZValue(6);
    addItem(enemy3);
    enemy3->setZValue(6);

    setSceneRect(0,0,block_size * grid_size,block_size * grid_size);
    //the grid of the map - 0's are paths, 1's are walls
        grid = {
            {1,1,1,1,1,1,1,0,1,1,1,0,1,1,1},
            {1,0,0,0,0,1,1,0,1,0,0,0,1,0,0},
            {1,0,1,1,0,0,0,0,1,0,0,0,1,1,1},
            {1,0,0,0,0,1,1,0,1,0,0,0,0,0,1},
            {1,0,1,1,0,1,0,0,1,1,1,0,1,1,1},
            {1,0,1,1,0,1,0,0,0,0,0,0,0,0,0},
            {1,0,1,1,0,1,0,1,1,0,1,1,1,1,1},
            {1,0,1,1,0,1,0,1,1,0,0,0,0,1,1},
            {1,0,0,0,0,0,0,0,0,0,1,1,0,0,1},
            {1,1,0,0,1,0,1,1,1,0,1,1,0,1,1},
            {1,0,0,1,1,1,1,0,1,0,0,0,0,1,1},
            {1,0,1,0,1,1,0,1,1,0,1,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,0,1,1,1,1,1},
            {1,0,0,1,1,1,1,0,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,0,0,0,0,0,0,1,1}
    };

    //Adding paths & edges to the map
    for(int i = 0; i < grid_size; i++){
        for(int j = 0; j < grid_size; j++){
            addRect(j * block_size, i * block_size, block_size, block_size, QPen(Qt::black), QBrush(grid[i][j] == 1 ? Qt::darkCyan : Qt::black));
            if(grid[i][j] == 0)
                myMap.addBlock(std::make_pair(j,i));
            if(j != grid_size - 1 && grid[i][j] == 0 && grid[i][j+1] == 0)  //not on the far right of the grid
                myMap.addEdge(std::make_pair(j,i), std::make_pair(j+1,i), 1);
            if(j != 0 && grid[i][j] == 0 && grid[i][j-1] == 0)              //not on the far left of the grid
                myMap.addEdge(std::make_pair(j,i), std::make_pair(j-1,i), 1);
            if(i != grid_size - 1 && grid[i][j] == 0 && grid[i+1][j] == 0)  //not on the bottom of the grid
                myMap.addEdge(std::make_pair(j,i), std::make_pair(j,i+1), 1);
            if(i != 0 && grid[i][j] == 0 && grid[i-1][j] == 0)              //not on the top of the grid
                myMap.addEdge(std::make_pair(j,i), std::make_pair(j,i-1), 1);
        }
    }

    createPath();
}

void CustomScene::createPath()      //Creates a visualization of shortest path
{
    deletePath();
    int dist = 0;
    std::vector<std::pair<int, int>> path;
    myMap.findShortestPath(std::make_pair(player->x() / block_size, player->y() / block_size), std::make_pair(12,14), dist, path);
    for (size_t i = 0; i < path.size() - 1; ++i) {
        Path* rect = new Path(
            path[i].first * block_size, path[i].second * block_size , block_size);
        rect->setPen(QPen(Qt::blue, 2));
        QColor blue20 = Qt::blue;
        blue20.setAlphaF( 0.2 );
        rect->setBrush(QBrush(blue20));
        rect->setZValue(4);
        addItem(rect);    }
}

void CustomScene::deletePath()      //deletes visualized path
{
    QList<Path*> pathsToRemove;

    for (QGraphicsItem* item : items()) {
        if (Path* p = dynamic_cast<Path*>(item) ) {
            pathsToRemove.append(p);
        }
    }

    for (Path* item : pathsToRemove) {
        removeItem(item);
        delete item;
    }
}

void CustomScene::keyPressEvent(QKeyEvent *event)           //determines the appropriate event when a specific key is pressed - movement
{
        if(event->key() == Qt::Key_Left){
        if(grid[player->y() / block_size][(player->x() - block_size) / block_size] == 0 )
                player->setX(player->x() - block_size);
        }

        else if (event->key() == Qt::Key_Right){
            if(grid[player->y() / block_size][(player->x() + block_size) / block_size] == 0 )
            player->setX(player->x() + block_size);
        }

        else if (event->key() == Qt::Key_Up){
            if(grid[(player->y() - block_size) / block_size][player->x() / block_size] == 0 )
            player->setY(player->y() - block_size);
        }

        else if (event->key() == Qt::Key_Down){
            if(grid[(player->y() + block_size) / block_size][player->x() / block_size] == 0 )
            player->setY(player->y() + block_size);
        }
        createPath();

        //check if player collided with goal
        QList<QGraphicsItem *> colliding_items = goal->collidingItems();
        for(QGraphicsItem* item : colliding_items) {
            if(Player* player = dynamic_cast<Player*>(item)) {
                    removeItem(player);
                    removeItem(goal);
                    delete player;
                    QMessageBox msgBox;
                    msgBox.setWindowTitle("Victory!!!");
                    msgBox.setText("You Ate The Burger :) ");
                    msgBox.setStandardButtons(QMessageBox::Ok);
                    msgBox.setDefaultButton(QMessageBox::Ok);
                    msgBox.exec();
                    QApplication::exit(1);
            }
        }

}
