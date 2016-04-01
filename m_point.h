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
    int step;
public:
    M_Point();
    M_Point(const QPoint pt,const int pr) : QPoint(pt),priority(pr){}
    M_Point(const int x,const int y,const int pr) : QPoint(x,y),priority(pr){}
    M_Point(const QPoint pt,const int pr,const int st) : QPoint(pt),priority(pr),step(st){ priority+=step; }
    M_Point(const int x,const int y,const int pr,const int st) : QPoint(x,y),priority(pr),step(st){ priority+=step; }

    int getPriority() const;
    void setPriority(int value);

    bool operator<(const M_Point op) const { return priority < op.priority; }
    bool operator>(const M_Point op) const { return priority > op.priority; }
    bool operator<=(M_Point op) const { return priority <= op.priority; }
    bool operator>=(M_Point op) const { return priority >= op.priority; }
    bool operator==(M_Point op) const { return priority == op.priority; }

    QPoint getPoint() const;
    int getStep() const;
    void setStep(int value);
};

}

#endif // M_POINT_H
