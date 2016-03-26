#ifndef MAP_H
#define MAP_H

#include <QString>
#include <QList>
#include <QPoint>

#include "heap.h"

#define WALL QChar('1')
#define ROAD QChar('0')

class Map
{
public:
    Map();
    ~Map();

    void set(int w,int h);              // set map of data
    void set(int w,int h,QString s);
    void set(QString s);
    char get_value(int x,int y) const;
    char get_state(int x,int y) const;
    void set_state(int x,int y,char s);

    bool find_road(int sx,int sy,int ex,int ey,int method);

    int getWidth() const;
    int getHeight() const;
    int getResult_step() const;
    int getVisit_step();
    bool getValid() const;

    enum{state_notdef = 0,state_unvisit = 1,state_visit = 2,state_solution = 4};
    enum{value_notdef = 0,value_road = 1,value_wall = 2};
    enum{method_None = 0,method_DFS = 1,method_BFS = 2,method_BestFirst};


private:
    bool valid;
    int width,height;
    int result_step;
    int visit_step;

    int Sx,Sy,Ex,Ey;


    int **value;
    int **state;
    QPoint **parent;
    QList<QPoint> p_mem;            // position memory
    Heap<QPoint,int> b_mem;         //bestfit emeory

    void _allocate_map(int w,int h);    // allocate map
    bool _dfs(int sx,int sy,int ex,int ey);
    bool _bfs(int sx,int sy,int ex,int ey);
    void _visit_append(const QPoint ch,const QPoint par,int method);

    bool _best_First(int sx,int sy,int ex,int ey);

};

#endif // MAP_H
