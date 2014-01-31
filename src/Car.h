#ifndef CAR_H_
#define CAR_H_

#include <memory>

class Direction;

class Car 
{
    struct Impl;
    std::unique_ptr<Impl> pImpl;
    
public:
    Car();
    ~Car();
    Direction Direction();
    void Update(int ms);
    void StartTurningLeft();
    void StartTurningRight();
    void StopTurning();

};

#endif