#include "m_point.h"

int M::M_Point::getPriority() const
{
    return priority;
}

void M::M_Point::setPriority(int value)
{
    priority = value;
}

M::M_Point::M_Point()
{
}

QPoint M::M_Point::get_Point() const
{
    return QPoint(x(),y());
}
