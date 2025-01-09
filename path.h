#ifndef PATH_H
#define PATH_H
#include <QGraphicsRectItem>
class Path : public QGraphicsRectItem
{
public:
    Path(int x, int y, int size);       //constructor -- this class is for the visualized shortest path
};

#endif // PATH_H
