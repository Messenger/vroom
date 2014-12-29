#ifndef VIEW_PORT_H_
#define VIEW_PORT_H_

#include <memory>

class Point;
class Distance;

class ViewPort
{
    struct Impl;
    std::unique_ptr<Impl> pImpl;
public:
    ViewPort();
    ~ViewPort();
    
    Point Offset() const;
    Distance Height() const;
    Distance Width() const;
    void Update(const Point& position);
};

#endif