#include "m_point.h"

int M::M_Point::getPriority() const
{
    return priority;
}

void M::M_Point::setPriority(int value)
{
    priority = value;
}

int M::M_Point::getStep() const
{
    return step;
}

void M::M_Point::setStep(int value)
{
    step = value;
}

M::M_Point::M_Point()
{
}

QPoint M::M_Point::getPoint() const
{
    return QPoint(x(),y());
}

