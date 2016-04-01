#ifndef M_POINT_H
#define M_POINT_H

#include <QPoint>

/*
 * This class is as same as QPoint.
 * but it has priority, integer value
 * and overload compare operator : <,>,<=,>=,==
 * this operator compare priority
 */

namespace M{

class M_Point : public QPoint
{
    int priority;
public:
    M_Point();
    M_Point(const QPoint pt,int pr) : QPoint(pt),priority(pr){}
    M_Point(const int x,const int y,const int pr) : QPoint(x,y),priority(pr){}

    int getPriority() const;
    void setPriority(int value);

    bool operator<(const M_Point op) const { return priority < op.priority; }
    bool operator>(const M_Point op) const { return priority > op.priority; }
    bool operator<=(M_Point op) const { return priority <= op.priority; }
    bool operator>=(M_Point op) const { return priority >= op.priority; }
    bool operator==(M_Point op) const { return priority == op.priority; }

    QPoint get_Point() const;
};

}

#endif // M_POINT_H
