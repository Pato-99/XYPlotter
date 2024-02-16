#ifndef XYPLOTTER_LINE_H
#define XYPLOTTER_LINE_H


struct Point
{
    int x;
    int y;

    Point() = delete;
    Point(int x, int y)
            : x(x), y(y)
    {}
    Point(const Point& p) = default;
    bool operator != (const Point& p) const;
};


class Line
{
private:
    Point startpoint;
    Point endpoint;

public:
    Line() = delete;
    Line(Point startpoint, Point endpoint)
            : startpoint(startpoint), endpoint(endpoint)
    {}

    class const_iterator
    {
    private:
        int dx, sx, dy, sy, err;
        Point current;
        bool termination = false;

    public:
        const_iterator() = delete;
        explicit const_iterator(Point start, Point end);
        const_iterator& operator++();
        const const_iterator operator++(int);
        Point& operator*();
        bool operator!= (const const_iterator& other);

    private:
        void line_util();
    };

    const_iterator begin();
    const_iterator end();

};

#endif //XYPLOTTER_LINE_H
