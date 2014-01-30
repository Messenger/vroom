#ifndef CAR_H_
#define CAR_H_

#include <memory>

class Car 
{
    struct Impl;
    std::unique_ptr<Impl> pImpl;
    
public:
    Car();
    ~Car();
    int Direction();
    void StartTurningLeft();
    void Update(int ms);
    void StopTurningLeft();    
};

#endif