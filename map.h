#ifndef MAP_H
#define MAP_H

#include <QString>
#include <QList>
#include <QPoint>

// std::stl
#include <queue>
#include <functional>
#include <vector>
#include <cmath>
using namespace std;

#include "m_point.h"
using namespace M;

#define WALL QChar('1')
#define ROAD QChar('0')

class Map
{
public:
    Map(int mtd);
    ~Map();

    void set(int w,int h);              // set map of data
    void set(int w,int h,QString s);
    void set(QString s);
    char get_value(int x,int y) const;
    char get_state(int x,int y) const;
    void set_state(int x,int y,char s);

    bool find_road(int sx,int sy,int ex,int ey);

    int getWidth() const;
    int getHeight() const;
    int getResult_step() const;
    int getVisit_step();
    bool getValid() const;

    enum{state_notdef = 0,state_unvisit = 1,state_visit = 2,state_solution = 4};
    enum{value_notdef = 0,value_road = 1,value_wall = 2};
    enum{method_None = 0,method_DFS = 1,method_BFS = 2,method_BestFirst = 3,method_A = 4,method_A_Star = 5};

    const int ax[8];
    const int ay[8];

    int getMethod() const;

private:
    bool valid;
    int width,height;
    int result_step;
    int visit_step;
    int Sx,Sy,Ex,Ey;
    int method;

    int **value;
    int **state;
    QPoint **parent;
    QList<QPoint> p_mem;                                                // position memorize(for DFS & BFS)

    priority_queue<M_Point,vector<M_Point>,greater<M_Point>> pp_mem;    //priority position memorize(for Best-First)

    void _allocate_map(int w,int h);    // allocate map
    bool _dfs(int sx,int sy,int ex,int ey);
    bool _bfs(int sx,int sy,int ex,int ey);
    void _visit_append(const QPoint ch,const QPoint par);

};

#endif // MAP_H
