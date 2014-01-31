#ifndef DIRECTION_H_
#define DIRECTION_H_

class Direction
{
public:
    Direction()
        : Update([] (int ms) { })
        , Value(0)
    {
    }
    
    std::function<void(int)> Update;
    int Value;
};

#endif