#include "map.h"

Map::Map(int mtd) :
    value(nullptr),
    state(nullptr),
    parent(nullptr),
    result_step(0),
    width(0),
    height(0),
    valid(false),
    visit_step(0),
    method(mtd)
{
}

Map::~Map()
{
    // release maze memory
    if(value != nullptr)
    {
        delete []value[0];
        delete []value;
    }
    if(state != nullptr)
    {
        delete []state[0];
        delete []state;
    }
    if(parent != nullptr)
    {
        delete []parent[0];
        delete []parent;
    }
}

void Map::set(int w, int h)
{
    _allocate_map(w,h);
}

void Map::set(int w, int h, QString s)
{
    _allocate_map(w,h);
    s = s.remove(' ').remove('\n').remove('\t').remove(',').remove('}').remove('{').remove('\'').remove(';');
    for(int i = 0 ; i < height ; ++i)
    {
        for(int j = 0 ; j < width ; ++j)
        {
            if(s.at(width*i+j) == WALL)
            {
                value[i+1][j+1] = value_wall;
            }
            if(s.at(width*i+j) == ROAD) value[i+1][j+1] = value_road;
            state[i+1][j+1] = state_unvisit;
        }
    }

}

void Map::set(QString s)
{
    int w,h;
    s = s.remove(' ').remove('\t').remove(',').remove('}').remove('{').remove('\'').remove(';');
    w = s.indexOf('\n');
    h = s.length()/w;
    s.remove('\n');
    set(w,h,s);
}


char Map::get_value(int x, int y) const
{
    return value[y+1][x+1];
}

char Map::get_state(int x, int y) const
{
    return state[y+1][x+1];
}

void Map::set_state(int x, int y, char s)
{
    if(s == state_unvisit && state[y+1][x+1] == state_visit) return;
    state[y+1][x+1] = s;
}

int Map::getWidth() const
{
    return width;
}

int Map::getHeight() const
{
    return height;
}

int Map::getResult_step() const
{
    return result_step;
}

int Map::getVisit_step()
{
    if(visit_step ==0)
    {
        for(int i=0;i<height;++i)
        {
            for(int j=0;j<width;++j)
            {
                if(state[i][j] == state_visit || state[i][j] == state_solution) ++visit_step;
            }
        }
    }
    return visit_step;
}

bool Map::getValid() const
{
    return valid;
}

int Map::getMethod() const
{
    return method;
}

bool Map::find_road(int sx, int sy, int ex, int ey)
{
    ++sx;++sy;++ex;++ey;            // inside of wall
    //invalid start/end point
    if(sx<1 || sy<1 || sx>width || sy>height || ex<1 || ey<1 || ex>width || ey>height) return false;
    if(value[sy][sx] == value_wall || value[ey][ex] == value_wall) return false;

    Sx = sx;Sy = sy;Ex = ex;Ey = ey;


    switch (method) {
    case method_BFS:
    case method_DFS:
        p_mem.clear();
        p_mem.append(QPoint(sx,sy));    // insert first point to backward
        break;

    case method_BestFirst:
    case method_A:
    case method_A_Star:
        while(!pp_mem.empty()) pp_mem.pop();
        int ky = (Ex-Sx)*(Ex-Sx)+(Ey-Sy)*(Ey-Sy);

        switch(method)
        {
        case method_BestFirst:
            pp_mem.push(M_Point(QPoint(Sx,Sy),ky));
            break;
        case method_A:
            pp_mem.push(M_Point(QPoint(Sx,Sy),ky,0));
            break;
        case method_A_Star:
            pp_mem.push(M_Point(QPoint(Sx,Sy),ky,0));
            break;
        }
        break;

    }

    QPoint current_point;

    while(!p_mem.empty() || !pp_mem.empty())
    {

        switch(method)
        {
        case method_BFS:
            current_point = p_mem.front();
            p_mem.pop_front();
            break;

        case method_DFS:
            current_point = p_mem.back();
            break;

        case method_BestFirst:
        case method_A:
        case method_A_Star:
            current_point = pp_mem.top().getPoint();
            visit_step = pp_mem.top().getStep();
            pp_mem.pop();
            break;
        }



        state[current_point.y()][current_point.x()] = state_visit;
        if(current_point.x() == ex && current_point.y() == ey) break;

        // find 8 way road
        // find up side
        if(value[current_point.y()-1][current_point.x()] == value_road && state[current_point.y()-1][current_point.x()] == state_unvisit)
        {
            _visit_append(QPoint(current_point.x(),current_point.y()-1),current_point);
            if(method == method_DFS) continue;
        }
        // find right-up side
        if(value[current_point.y()-1][current_point.x()+1] == value_road && state[current_point.y()-1][current_point.x()+1] == state_unvisit)
        {
            _visit_append(QPoint(current_point.x()+1,current_point.y()-1),current_point);
            if(method == method_DFS) continue;
        }
        // find right side
        if(value[current_point.y()][current_point.x()+1] == value_road && state[current_point.y()][current_point.x()+1] == state_unvisit)
        {
            _visit_append(QPoint(current_point.x()+1,current_point.y()),current_point);
            if(method == method_DFS) continue;
        }
        // find down-right side
        if(value[current_point.y()+1][current_point.x()+1] == value_road && state[current_point.y()+1][current_point.x()+1] == state_unvisit)
        {
            _visit_append(QPoint(current_point.x()+1,current_point.y()+1),current_point);
            if(method == method_DFS) continue;
        }
        // find down side
        if(value[current_point.y()+1][current_point.x()] == value_road && state[current_point.y()+1][current_point.x()] == state_unvisit)
        {
            _visit_append(QPoint(current_point.x(),current_point.y()+1),current_point);
            if(method == method_DFS) continue;
        }
        // find down-left side
        if(value[current_point.y()+1][current_point.x()-1] == value_road && state[current_point.y()+1][current_point.x()-1] == state_unvisit)
        {
            _visit_append(QPoint(current_point.x()-1,current_point.y()+1),current_point);
            if(method == method_DFS) continue;
        }
        // find left side
        if(value[current_point.y()][current_point.x()-1] == value_road && state[current_point.y()][current_point.x()-1] == state_unvisit)
        {
            _visit_append(QPoint(current_point.x()-1,current_point.y()),current_point);
            if(method == method_DFS) continue;
        }
        // find up-left side
        if(value[current_point.y()-1][current_point.x()-1] == value_road && state[current_point.y()-1][current_point.x()-1] == state_unvisit)
        {
            _visit_append(QPoint(current_point.x()-1,current_point.y()-1),current_point);
            if(method == method_DFS) continue;
        }

        if(method == method_DFS) p_mem.pop_back();
    }

    visit_step = 0;
    // find solution road
    result_step = 0;
    while(true)
    {
        state[current_point.y()][current_point.x()] = state_solution;
        if(current_point.x() == sx && current_point.y() == sy) break;
        ++result_step;
        current_point = parent[current_point.y()][current_point.x()];
    }

    return true;
}

void Map::_allocate_map(int w, int h)
{
    width = w;              // real width
    height = h;             // real height
    w+=2;                   // width with wall
    h+=2;                   // height with wall

    // allocate value
    if(value != nullptr)
    {
        delete []value[0];
        delete []value;
    }
    value = new int*[h];
    value[0] = new int[w*h];
    for(int i=1;i<h;++i) value[i] = value[i-1]+w;

    // allocate state

    if(state != nullptr)
    {
        delete []state[0];
        delete []state;
    }
    state = new int*[h];
    state[0] = new int[w*h];
    for(int i=1;i<h;++i) state[i] = state[i-1]+w;

    if(parent != nullptr)
    {
        delete []parent[0];
        delete []parent;
    }
    parent = new QPoint*[h];
    parent[0] = new QPoint[w*h];
    for(int i=1;i<h;++i) parent[i] = parent[i-1]+w;

    // surround maze with walls
    for(int i=0;i<h;++i)
    {
        value[i][0] = value[i][w-1] = value_wall;
        state[i][0] = state[i][w-1] = state_notdef;
    }
    for(int i=0;i<w;++i)
    {
        value[0][i] = value[h-1][i] = value_wall;
        state[0][i] = state[h-1][i] = state_notdef;
    }
    valid = true;
}

void Map::_visit_append(const QPoint ch, const QPoint par)
{
    int disx,disy;
    disx = ch.x()-Ex;
    disy = ch.y()-Ey;

// what is the best huristic ?
    int prio = (disx*disx+disy*disy);
//    prio = sqrt(disx*disx+disy*disy);
//    prio = abs(ch.x()-Ex) + abs(ch.y()-Ey);

    switch(method)
    {
    case method_BFS:
    case method_DFS:
        p_mem.append(ch);
        break;

    case method_BestFirst:
        pp_mem.push(M_Point(ch,prio));
        break;

    case method_A:
        pp_mem.push(M_Point(ch,prio,(visit_step+1)));
        break;

    case method_A_Star:
        pp_mem.push(M_Point(ch,0,(visit_step+1)));
        break;
    }
    state[ch.y()][ch.x()] = state_visit;
    parent[ch.y()][ch.x()] = par;
}
