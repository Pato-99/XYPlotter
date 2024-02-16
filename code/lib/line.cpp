#include <cmath>

#include "line.h"


bool Point::operator != (const Point& p) const
{
    return x != p.x || y != p.y;
}

Line::const_iterator::const_iterator(Point start, Point end)
        : current(start)
{
    dx = std::abs(end.x - start.x);
    sx = start.x < end.x ? 1 : -1;
    dy = -std::abs(end.y - start.y);
    sy = start.y < end.y ? 1 : -1;
    err = dx + dy;
}

Line::const_iterator& Line::const_iterator::operator++()
{
    line_util();
    return *this;
}

const Line::const_iterator Line::const_iterator::operator++(int)
{
    const const_iterator tmp = *this;
    line_util();
    return tmp;
}

Point& Line::const_iterator::operator*()
{
    return current;
}

bool Line::const_iterator::operator!= (const const_iterator& other)
{
    if (! (current != other.current) ) {
        termination = true;
        return true;
    }
    return !termination;
}

void Line::const_iterator::line_util()
{
    int e2 = 2 * err;
    if (e2 >= dy) {
        err += dy;
        current.x += sx;
    }
    if (e2 <= dx) {
        err += dx;
        current.y += sy;
    }
}

Line::const_iterator Line::begin()
{
    Line::const_iterator it(startpoint, endpoint);
    return it;
}

Line::const_iterator Line::end()
{
    Line::const_iterator it(endpoint, endpoint);
    return it;
}
